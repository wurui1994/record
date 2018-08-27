@set PATH=%~dp0
@set PLUGIN_PATH=%~dp0\plugins+
@set VSFilter=LoadPlugin("%PLUGIN_PATH%\VSFilter.dll")
@set FFMS2=LoadPlugin("%PLUGIN_PATH%\ffms2.dll")
@set VPATH=vPath="%~dpn1.mkv"
@set ASSPATH=assPath="%~dpn1.ass"
@echo %VSFilter% > %~dp0build.avs
@echo %FFMS2% >> %~dp0build.avs
@echo %VPATH% >> %~dp0build.avs
@echo %ASSPATH% >> %~dp0build.avs
@type %~dp0demo.avs >> %~dp0build.avs
ffmpeg.exe -v 9 -loglevel 99 -t 60 -i "%~dp0build.avs" -vcodec libx264 -acodec aac -keyint_min 5 -g 10 -sc_threshold 0 -map_metadata -1 -map_chapters -1 -f mp4 -y "%~dp1product.mp4"
pause