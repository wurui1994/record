# rust actix
cd actix && cargo run --release
# node
node test.js
# golang
go run test.go
# python sanic
pip install sanic
python test.py

# `apib` tool: https://github.com/apigee/apib 
apib -c1 -d10 http://127.0.0.1:8000/
apib -c100 -d10 http://127.0.0.1:8000/

# `wrk` tool: https://github.com/wg/wrk
wrk http://127.0.0.1:8000/

# `bombardier` tool: https://github.com/codesenberg/bombardier
bombardier http://127.0.0.1:8000/
bombardier http://127.0.0.1:8000/ -d3s -c100
