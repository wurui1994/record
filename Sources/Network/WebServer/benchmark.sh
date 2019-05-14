# rust actix
cd actix && cargo run --release
# node
node test.js
# golang
go run test.go
# python sanic
pip install sanic
python test.py

# `apid` tool: https://github.com/apigee/apib 
apid -c1 -d10 http://localhost:8000/
apid -c100 -d10 http://localhost:8000/