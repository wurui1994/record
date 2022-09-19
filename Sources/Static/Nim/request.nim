import std/httpclient
var client = newHttpClient()
echo client.getContent("http://baidu.com/")

import std/asyncdispatch

proc asyncProc(): Future[string] {.async.} =
  var client = newAsyncHttpClient()
  return await client.getContent("http://baidu.com/")

echo waitFor asyncProc()