{
	"targets": [
		{
			"target_name": "xmrigCpu",
			"include_dirs": [
				"src",
				"<!(node -e \"require('nan')\")",
				"src/3rdparty",
				"src/3rdparty/libcpuid"
			],
			"sources": [
				"src/3rdparty/libcpuid/asm-bits.c",
				"src/3rdparty/libcpuid/recog_amd.c",
				"src/3rdparty/libcpuid/recog_intel.c",
				"src/3rdparty/libcpuid/libcpuid_util.c",
				"src/3rdparty/libcpuid/cpuid_main.c",
				"src/backend/cpu/CpuThread.cpp",
				"src/backend/common/Hashrate.cpp",
				"src/backend/common/Worker.cpp",
				"src/backend/common/Workers.cpp",
				"src/backend/cpu/Cpu.cpp",
				"src/base/io/Console.cpp",
				"src/base/io/log/backends/ConsoleLog.cpp",
				"src/base/io/log/backends/FileLog.cpp",
				"src/base/io/log/Log.cpp",
				"src/base/net/stratum/Client.cpp",
				"src/base/net/stratum/Job.cpp",
				"src/base/net/stratum/Pool.cpp",
				"src/base/net/stratum/strategies/FailoverStrategy.cpp",
				"src/base/net/stratum/strategies/SinglePoolStrategy.cpp",
				"src/base/kernel/Platform.cpp",
				"src/core/config/Config.cpp",
				"src/core/Controller.cpp",
				"src/crypto/common/Algorithm.cpp",
				"src/crypto/common/keccak.cpp",
				"src/crypto/cn/c_groestl.c",
				"src/crypto/cn/c_blake256.c",
				"src/crypto/cn/c_jh.c",
				"src/crypto/cn/c_skein.c",
				"src/net/Network.cpp",
				"src/net/NetworkState.cpp",
				"src/net/strategies/DonateStrategy.cpp",
				"src/NodeApp.cpp",
				"src/NodeXmrigCpu.cpp",
				"src/Summary.cpp",
				"src/xmrig.cpp"
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
				"-Wno-unused-variable"
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
							'src/App_win.cpp',
							'src/base/kernel/Platform_win.cpp'
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
							'src/App_unix.cpp',
							'src/base/kernel/Platform_mac.cpp'
						],
						'xcode_settings':
						{
							'OTHER_CFLAGS': ['-maes']
						}

					},
					'OS=="linux"',
					{
						'sources': [
							'src/App_unix.cpp',
							'src/base/kernel/Platform_unix.cpp'
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

