aria2c --enable-rpc --rpc-listen-all --rpc-allow-origin-all --rpc-listen-port=6800 -D

curl -X POST -d '{"jsonrpc":"2.0","id":"donwload","method":"aria2.addUri","params":[["https://www.baidu.com"]]}' --header "Content-Type:application/json" 'http://localhost:6800/jsonrpc'

curl -X POST -d '{"jsonrpc":"2.0","id":"donwload","method":"aria2.addUri","params":[["https://sm.myapp.com/original/Compression/7z1805-x64.exe"]]}' --header "Content-Type:application/json" 'http://localhost:6800/jsonrpc'

curl -X POST -d '{"jsonrpc":"2.0","id":"donwload","method":"aria2.addUri","params":[["https://sm.myapp.com/original/Compression/BANDIZIP-SETUP-6.14.0.0.EXE"]]}' --header "Content-Type:application/json" 'http://localhost:6800/jsonrpc'

# pkill -f aria2c