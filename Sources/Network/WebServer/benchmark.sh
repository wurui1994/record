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