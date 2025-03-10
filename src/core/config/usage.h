/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
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

#ifndef XMRIG_USAGE_H
#define XMRIG_USAGE_H


#include "version.h"


#include <string>


namespace xmrig {


static inline const std::string &usage()
{
    static std::string u;

    if (!u.empty()) {
        return u;
    }

    u += "Usage: " APP_ID " [OPTIONS]\n\nNetwork:\n";
    u += "  -o, --url=URL                 URL of mining server\n";
    u += "  -a, --algo=ALGO               mining algorithm https://xmrig.com/docs/algorithms\n";
    u += "      --coin=COIN               specify coin instead of algorithm\n";
    u += "  -u, --user=USERNAME           username for mining server\n";
    u += "  -p, --pass=PASSWORD           password for mining server\n";
    u += "  -O, --userpass=U:P            username:password pair for mining server\n";
    u += "  -k, --keepalive               send keepalived packet for prevent timeout (needs pool support)\n";
    u += "      --nicehash                enable nicehash.com support\n";
    u += "      --rig-id=ID               rig identifier for pool-side statistics (needs pool support)\n";

#   ifdef XMRIG_FEATURE_TLS
    u += "      --tls                     enable SSL/TLS support (needs pool support)\n";
    u += "      --tls-fingerprint=HEX     pool TLS certificate fingerprint for strict certificate pinning\n";
#   endif

#   ifdef XMRIG_FEATURE_HTTP
    u += "      --daemon                  use daemon RPC instead of pool for solo mining\n";
    u += "      --daemon-poll-interval=N  daemon poll interval in milliseconds (default: 1000)\n";
    u += "      --self-select=URL         self-select block templates from URL\n";
#   endif

    u += "  -r, --retries=N               number of times to retry before switch to backup server (default: 5)\n";
    u += "  -R, --retry-pause=N           time to pause between retries (default: 5)\n";
    u += "      --user-agent              set custom user-agent string for pool\n";
    u += "      --donate-level=N          donate level, default 5%% (5 minutes in 100 minutes)\n";
    u += "      --donate-over-proxy=N     control donate over xmrig-proxy feature\n";

    u += "\nCPU backend:\n";

    u += "      --no-cpu                  disable CPU mining backend\n";
    u += "  -t, --threads=N               number of CPU threads\n";
    u += "  -v, --av=N                    algorithm variation, 0 auto select\n";
    u += "      --cpu-affinity            set process affinity to CPU core(s), mask 0x3 for cores 0 and 1\n";
    u += "      --cpu-priority            set process priority (0 idle, 2 normal to 5 highest)\n";
    u += "      --cpu-max-threads-hint=N  maximum CPU threads count (in percentage) hint for autoconfig\n";
    u += "      --cpu-memory-pool=N       number of 2 MB pages for persistent memory pool, -1 (auto), 0 (disable)\n";
    u += "      --no-huge-pages           disable huge pages support\n";
    u += "      --asm=ASM                 ASM optimizations, possible values: auto, none, intel, ryzen, bulldozer\n";

#   ifdef XMRIG_ALGO_RANDOMX
    u += "      --randomx-init=N          threads count to initialize RandomX dataset\n";
    u += "      --randomx-no-numa         disable NUMA support for RandomX\n";
#   endif

#   ifdef XMRIG_FEATURE_HTTP
    u += "\nAPI:\n";
    u += "      --api-worker-id=ID        custom worker-id for API\n";
    u += "      --api-id=ID               custom instance ID for API\n";
    u += "      --http-host=HOST          bind host for HTTP API (default: 127.0.0.1)\n";
    u += "      --http-port=N             bind port for HTTP API\n";
    u += "      --http-access-token=T     access token for HTTP API\n";
    u += "      --http-no-restricted      enable full remote access to HTTP API (only if access token set)\n";
#   endif

#   ifdef XMRIG_FEATURE_OPENCL
    u += "\nOpenCL backend:\n";
    u += "      --opencl                  enable OpenCL mining backend\n";
    u += "      --opencl-devices=N        comma separated list of OpenCL devices to use\n";
    u += "      --opencl-platform=N       OpenCL platform index or name\n";
    u += "      --opencl-loader=PATH      path to OpenCL-ICD-Loader (OpenCL.dll or libOpenCL.so)\n";
    u += "      --opencl-no-cache         disable OpenCL cache\n";
    u += "      --print-platforms         print available OpenCL platforms and exit\n";
#   endif

#   ifdef XMRIG_FEATURE_CUDA
    u += "\nCUDA backend:\n";
    u += "      --cuda                    enable CUDA mining backend\n";
    u += "      --cuda-loader=PATH        path to CUDA plugin (xmrig-cuda.dll or libxmrig-cuda.so)\n";
    u += "      --cuda-devices=N          comma separated list of CUDA devices to use\n";
    u += "      --cuda-bfactor-hint=N     bfactor hint for autoconfig (0-12)\n";
    u += "      --cuda-bsleep-hint=N      bsleep hint for autoconfig\n";
#   endif
#   ifdef XMRIG_FEATURE_NVML
    u += "      --no-nvml                 disable NVML (NVIDIA Management Library) support\n";
#   endif

    u += "\nLogging:\n";

#   ifdef HAVE_SYSLOG_H
    u += "  -S, --syslog                  use system log for output messages\n";
#   endif

    u += "  -l, --log-file=FILE           log all output to a file\n";
    u += "      --print-time=N            print hashrate report every N seconds\n";
#   ifdef XMRIG_FEATURE_NVML
    u += "      --health-print-time=N     print health report every N seconds\n";
#   endif
    u += "      --no-color                disable colored output\n";

    u += "\nMisc:\n";

    u += "  -c, --config=FILE             load a JSON-format configuration file\n";
    u += "  -j, --config-jsonraw=string   load a JSON-format configuration string\n";
    u += "  -B, --background              run the miner in the background\n";
    u += "  -V, --version                 output version information and exit\n";
    u += "  -h, --help                    display this help and exit\n";
    u += "      --dry-run                 test configuration and exit\n";

#   ifdef XMRIG_FEATURE_HWLOC
    u += "      --export-topology         export hwloc topology to a XML file and exit\n";
#   endif

    return u;
}


} /* namespace xmrig */

#endif /* XMRIG_USAGE_H */
