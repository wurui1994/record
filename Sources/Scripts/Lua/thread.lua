local Threads = require "llthreads2.ex"
function loop()
    while(1)do end
end
local thread = Threads.new(loop)
thread:start()
loop()
thread:join()