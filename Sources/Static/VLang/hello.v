import time
import net.http
resp := http.get('https://vlang.io/utc_now') or {
    println('failed to fetch data from the server')
    return
}
t := time.unix(resp.body.int())
println(t.format()) // 2019-08-16 17:48