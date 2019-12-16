{
	"targets": [
		{
			"target_name": "xmrigCpu",
			"include_dirs": [
				"src",
				"<!(node -e \"require('nan')\")",
				"src/3rdparty",
				"src/3rdparty/libcpuid",
				"src/3rdparty/rapidjson"
			],
			"sources": [
				"src/backend/cpu/Cpu.cpp",
				"src/backend/cpu/CpuBackend.cpp",
				"src/backend/cpu/CpuConfig.cpp",
				"src/backend/cpu/CpuThreads.cpp",
				"src/backend/cpu/platform/BasicCpuInfo.cpp",
				"src/backend/common/Hashrate.cpp",
				"src/backend/common/Threads.cpp",
				"src/backend/common/Workers.cpp",
				"src/base/io/Console.cpp",
				"src/base/io/json/Json.cpp",
				"src/base/io/json/JsonChain.cpp",
				"src/base/io/json/JsonRequest.cpp",
				"src/base/io/log/backends/ConsoleLog.cpp",
				"src/base/io/log/Log.cpp",
				"src/base/kernel/config/BaseConfig.cpp",
				"src/base/kernel/config/BaseTransform.cpp",
				"src/base/kernel/Base.cpp",
				"src/base/kernel/Platform.cpp",
				"src/base/kernel/Process.cpp",
				"src/base/kernel/Signals.cpp",
				"src/base/net/dns/Dns.cpp",
				"src/base/net/dns/DnsRecord.cpp",
				"src/base/net/http/Http.cpp",
				"src/base/net/stratum/BaseClient.cpp",
				"src/base/net/stratum/Client.cpp",
				"src/base/net/stratum/Pool.cpp",
				"src/base/net/stratum/Pools.cpp",
				"src/base/net/stratum/Url.cpp",
				"src/base/net/stratum/strategies/FailoverStrategy.cpp",
				"src/base/net/stratum/strategies/SinglePoolStrategy.cpp",
				"src/base/tools/Arguments.cpp",
				"src/base/tools/Buffer.cpp",
				"src/base/tools/String.cpp",
				"src/base/tools/Timer.cpp",
				"src/core/config/Config.cpp",
				"src/core/config/ConfigTransform.cpp",
				"src/core/Controller.cpp",
				"src/core/Miner.cpp",
				"src/crypto/common/Algorithm.cpp",
				"src/crypto/common/Coin.cpp",
				"src/crypto/common/MemoryPool.cpp",
				"src/crypto/common/Nonce.cpp",
				"src/crypto/common/VirtualMemory.cpp",
				"src/net/JobResults.cpp",
				"src/net/Network.cpp",
				"src/net/NetworkState.cpp",
				"src/NodeApp.cpp",
				"src/NodeXmrig.cpp",
				"src/NodeXmrigCpu.cpp",
				"src/Summary.cpp"
			],
			'cflags!': [
				'-pthread'
			],
			'cflags': [
				"-maes"
			],
			'cflags_cc!': [
				'-std=gnu++0x'
			],
			"cflags_cc": [
				"-std=c++11",
				"-maes",
				"-Wno-unused-variable",
				"-Wno-empty-body"
			],
			'defines': [
				'UNICODE',
				'RAPIDJSON_SSE2',
				'XMRIG_NO_HTTPD',
				'XMRIG_NO_API',
				'_GNU_SOURCE'
			],
			'conditions': [
				[
					'OS=="win"',
					{
						'sources': [
							'res/app.rc',
							'src/NodeApp_win.cpp',
							'src/base/io/json/Json_win.cpp',
							'src/base/kernel/Platform_win.cpp',
							'src/crypto/common/VirtualMemory_win.cpp'
						],
						"defines": [
							"WIN32"
						],
						"link_settings": {
							"libraries": [
								"-lws2_32",
								"-lpsapi",
								"-liphlpapi",
								"-luserenv"
							]
						}
					},
					'OS=="mac"',
					{
						'sources': [
							'src/NodeApp_unix.cpp',
							'src/base/io/json/Json_unix.cpp',
							'src/base/kernel/Platform_mac.cpp',
							'src/crypto/common/VirtualMemory_unix.cpp'
						],
						'xcode_settings':
						{
							'OTHER_CFLAGS': ['-maes']
						}

					},
					'OS=="linux"',
					{
						'sources': [
							'src/NodeApp_unix.cpp',
							'src/base/io/json/Json_unix.cpp',
							'src/base/kernel/Platform_unix.cpp',
							'src/crypto/common/VirtualMemory_unix.cpp'
						],
						'defines': [
							'NDEBUG',
							'XMRIG_NO_IPBC',
							'__STDC_FORMAT_MACROS'
						],
						"link_settings": {
							"libraries": [
								"-lrt"
							]
						}
					}
				]
			]
		}
	]
}

