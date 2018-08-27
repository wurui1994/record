@set PATH=%~dp0
@set PLUGIN_PATH=%~dp0\plugins+
@set VSFilter=LoadPlugin("%PLUGIN_PATH%\VSFilter.dll")
@set FFMS2=LoadPlugin("%PLUGIN_PATH%\ffms2.dll")
@set VPATH=vPath="%~dpn1.mkv"
@set ASSPATH=assPath="%~dpn1.ass"
@echo %VSFilter% > %~dp0play.avs
@echo %FFMS2% >> %~dp0play.avs
@echo %VPATH% >> %~dp0play.avs
@echo %ASSPATH% >> %~dp0play.avs
@type %~dp0demo.avs >> %~dp0play.avs
REM ffplay.exe -f avisynth %~dp0play.avs
ffplay -i %~dp0play.avs
@pause