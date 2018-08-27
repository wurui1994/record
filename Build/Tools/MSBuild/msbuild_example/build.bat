REM msbuild build.xml
REM msbuild build.xml /t:run /nologo
REM msbuild build.xml /t:clean
msbuild build.xml /t:build,run,clean /nologo
