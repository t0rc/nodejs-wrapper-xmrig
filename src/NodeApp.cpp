/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2016-2018 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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


#include <stdlib.h>
#include <uv.h>


#include "base/api/Api.h"
#include "NodeApp.h"
#include "base/io/Console.h"
#include "base/io/log/Log.h"
#include "base/kernel/Platform.h"
#include "core/config/Config.h"
#include "core/Controller.h"
#include "backend/cpu/Cpu.h"
#include "crypto/cn/CryptoNight.h"
#include "Mem.h"
#include "net/Network.h"
#include "Summary.h"
#include "version.h"
#include "backend/common/Workers.h"

#include "base/kernel/Process.h"
#include "base/kernel/Signals.h"

#include <string>


NodeApp *NodeApp::m_self = nullptr;


NodeApp::NodeApp(const std::string jsonConfig) :
//    m_console(nullptr),
    m_httpd(nullptr)
{
    m_self = this;

	int argc = 0;
	char** argv = nullptr;
	xmrig::Process process(argc,argv);

    m_controller = new xmrig::Controller(&process);
    //m_controller = new xmrig::Controller();

    if (m_controller->init() != 0) {
        return;
    }
}


NodeApp::~NodeApp()
{
//    delete m_signals;
//    delete m_console;
    delete m_controller;
}


int NodeApp::exec()
{
    if (!m_controller->isReady()) {
        return 2;
    }

    background();
    //m_signals = new xmrig::Signals(this);

    const xmrig::CpuConfig config;

//    Mem::init(m_controller->config()->isHugePages());
    Mem::init(config.isHugePages());

    xmrig::Summary::print(m_controller);

    if (m_controller->config()->isDryRun()) {
        LOG_NOTICE("OK");
        release();

        return 0;
    }

    m_controller->start();
    m_controller->network()->connect();

    release();
    return 0;
}


void NodeApp::reloadConfig(const rapidjson::Value jsonConfig)
{
//	xmrig::Workers::restart(); // Method restart does not exists...


//    if (m_controller->reloadConfig(jsonConfig) != 0) {
//        return;
//    }

    if (m_controller->reload(jsonConfig) != 0) {
        return;
    }
}


void NodeApp::onConsoleCommand(char command)
{

}


void NodeApp::close()
{
//    m_controller->network()->stop();
    m_controller->stop();

    xmrig::Workers<xmrig::CpuLaunchData> workers;
    workers.stop();

    uv_stop(uv_default_loop());
}

std::string NodeApp::getStatus()
{
//  return xmrig::Workers::getHashrate(true);
//	xmrig::Workers<xmrig::CpuLaunchData> workers;
//	return workers.hashrate();

//	xmrig::Hashrate hashrate;

	return "";
};


void NodeApp::release()
{
}
