/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018      Lee Clagett <https://github.com/vtnerd>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <cstdlib>

#include <uv.h>

#include "NodeApp.h"
#include "base/io/Console.h"
#include "base/io/log/Log.h"
#include "base/kernel/Signals.h"
#include "base/kernel/Process.h"
#include "core/config/Config.h"
#include "core/Controller.h"
#include "core/Miner.h"
#include "Summary.h"

#define COMMAND_NAME "nodeXmrig"
#define OPTION_JSON  "--config-jsonraw="


xmrig::NodeApp::NodeApp(const std::string jsonConfig)
{
    constexpr size_t command_size = sizeof(COMMAND_NAME);
    const size_t buffer_size = command_size + sizeof(OPTION_JSON) + jsonConfig.size(); 
    char argv_buffer[buffer_size];

    strcpy(argv_buffer, COMMAND_NAME);
    strcpy(argv_buffer + command_size, OPTION_JSON);
    strcat(argv_buffer + command_size, jsonConfig.c_str());

    const char* argv[2] = { argv_buffer, argv_buffer + command_size };

    xmrig::Process process(2, (char**) argv);

    m_controller = new xmrig::Controller(&process);
    if (m_controller->init() != 0)
        return;
}


xmrig::NodeApp::~NodeApp()
{
    delete m_console;
    delete m_controller;
    delete m_signals;
}


int xmrig::NodeApp::exec()
{
    if (!m_controller->isReady())
        return 2;

    m_signals = new Signals(this);

    int rc = 0;
    if (background(rc))
        return rc;

    if (!m_controller->isBackground())
        m_console = new Console(this);

    xmrig::Summary::print(m_controller);

    if (m_controller->config()->isDryRun())
    {
        LOG_NOTICE("OK");
        return 0;
    }

    m_controller->start();

    rc = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());

    return rc;
}


void xmrig::NodeApp::reloadConfig(const rapidjson::Value jsonConfig)
{
    m_controller->stop();

    if (!m_controller->reload(jsonConfig))
        return;

    m_controller->start();
}


void xmrig::NodeApp::onConsoleCommand(char command)
{
    if (command == 3) {
        LOG_WARN("Ctrl+C received, exiting");
        close();
    }
    else {
        m_controller->miner()->execCommand(command);
    }
}


void xmrig::NodeApp::onSignal(int signum)
{
    switch (signum)
    {
    case SIGHUP:
        LOG_WARN("SIGHUP received, exiting");
        break;

    case SIGTERM:
        LOG_WARN("SIGTERM received, exiting");
        break;

    case SIGINT:
        LOG_WARN("SIGINT received, exiting");
        break;

    default:
        return;
    }

    close();
}


void xmrig::NodeApp::close()
{
    m_signals->stop();

    if (m_console)
        m_console->stop();

    m_controller->stop();

    uv_stop(uv_default_loop());

    Log::destroy();
}


std::string xmrig::NodeApp::getStatus()
{
    return m_controller->miner()->getHashrate(true);
};
