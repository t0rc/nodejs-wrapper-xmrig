// this is how we will require our module
//const xmrigCpu = require('./')

var xmrigCpu

if (process.env.DEBUG) {
    xmrigCpu= require('./build/Debug/xmrigCpu.node')
} else {
    xmrigCpu= require('./build/Release/xmrigCpu.node')
}

module.exports = xmrigCpu

var jsonConfig = {
    "api": {
        "id": null,
        "worker-id": null
    },
    "http": {
        "enabled": false,
        "host": "127.0.0.1",
        "port": 0,
        "access-token": null,
        "restricted": true
    },
    "autosave": true,
    "version": 1,
    "background": false,
    "colors": true,
    "randomx": {
        "init": -1,
        "numa": true
    },
    "cpu": {
        "affinity": null,
        "enabled": true,
        "huge-pages": true,
        "hw-aes": null,
        "priority": null,
        "memory-pool": false,
        "max-threads-hint": 100,
        "threads": null,
        "asm": true,
        "argon2-impl": null,
        "cn/0": false,
        "cn-lite/0": false
    },
    "opencl": {
        "enabled": false,
        "cache": true,
        "loader": null,
        "platform": "AMD",
        "cn/0": false,
        "cn-lite/0": false
    },
    "cuda": {
        "enabled": false,
        "loader": null,
        "nvml": true,
        "cn/0": false,
        "cn-lite/0": false
    },
    "donate-level": 0,
    "donate-over-proxy": 1,
    "log-file": null,
    "pools": [
        {
            "algo": "rx/sfx",
            "coin": null,
            "url": "donate.v2.xmrig.com:3333",
            "user": "YOUR_WALLET_ADDRESS",
            "pass": "x",
            "rig-id": null,
            "nicehash": false,
            "keepalive": false,
            "enabled": true,
            "tls": false,
            "tls-fingerprint": null,
            "daemon": false,
            "self-select": null
        }
    ],
    "print-time": 60,
    "health-print-time": 60,
    "retries": 5,
    "retry-pause": 5,
    "syslog": false,
    "user-agent": null,
    "watch": true
} ;

var userWallet = "SFXtzS2TXfSZu4XJh8sRNsF7iqe66dWX8NByr3CGDwM45Bo8tbsNuwffaTbjSr6Eqd9ihBB3WmTB3ftS4aNqDz9EMapGkh6FJKG";
//var pool = "safex.luckypool.io:3366";
var pool = "pool.safexnews.net:5555";
var pool2 = "pool.safexnews.net:1111";

jsonConfig.pools[0].url = pool;
jsonConfig.pools[0].user = userWallet;

console.log("JS: User address:"+userWallet);
console.log("JS: Pool:"+pool);

var miner = null;
var counter = 0;

console.log("JS: Starting mining...");
miner = new xmrigCpu.NodeXmrigCpu(JSON.stringify(jsonConfig));
miner.startMining();
console.log("JS: Native mining started!");


function stopMining(arg) {
    counter++;
    console.log("stopMining counter:" + counter);

    console.log("JS: Ending mining...");
    miner.stopMining();
    console.log("JS: Mining ended");

    setTimeout(checkStatus, 2000);
}

function startMining(arg) {
    jsonConfig.pools[0].url = pool2;

    //here reload config
    console.log("JS: Reloading config...");
    miner.reloadConfig(JSON.stringify(jsonConfig));
    counter++;
    console.log("startMining counter:" + counter);

    console.log("JS: Starting mining...");
    miner.startMining();
    console.log("JS: Mining started");

    setTimeout(checkStatus, 2000);
}

function checkStatus(arg) {
    console.log("JS: Hashrate:" + miner.getStatus());
    counter++;
    console.log("checkStatus counter:" + counter);

    if (counter < 20) {
        setTimeout(checkStatus, 1000);
    } else if (counter == 20) {
        setTimeout(stopMining, 2000);
    } else if (counter == 35) {
        setTimeout(startMining, 1000);
    } else if (counter == 200) {
        setTimeout(stopMining, 1000);
    } else {
        setTimeout(checkStatus, 1000);
    }
}

setTimeout(checkStatus, 2000);
