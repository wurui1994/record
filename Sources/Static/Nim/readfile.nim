var test:string = "hello"
echo test
test = "world"
echo test

var line:string
let f = open("readfile.nim")
while f.readLine(line):
    echo line