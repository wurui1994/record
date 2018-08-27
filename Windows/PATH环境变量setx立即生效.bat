set tmp=%path%
echo %tmp%

setx path "test"
path
set path "test"

REM reset
set path %tmp%
setx path %tmp%

REM set只会修改当前cmd环境变量，setx只会修改系统环境变量【资源管理器生效】。
REM reg add path 对新建或重启的资源管理器生效
REM https://technet.microsoft.com/en-us/library/cc755104(v=ws.11).aspx