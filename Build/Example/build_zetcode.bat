@echo off
@REM git clone https://github.com/janbodnar/Windows-API-examples.git
@REM cl不支持cpp变长数组(vla), zetcode使用的是Pelles(http://www.smorgasbordet.com/pellesc/)
@REM pellesc不开源 建议使用mingw gcc编译 `gcc -municode -mwindows`
if "%1" == "clean" goto :clean
if "%1" == "run" goto :run

:build
echo building
pushd %cd%
call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
popd %cd%

pushd %cd%
cd Windows-API-examples
for /r %%f in (*.c) do cd %%~dpf & if not exist %%~dpnf.exe (cl /nologo %%f kernel32.lib user32.lib gdi32.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib)
popd %cd%
goto :eof

:run
echo running
cd Windows-API-examples
pushd %cd%
for /r %%f in (*.c) do if exist %%~dpnf.exe (echo Run %%~dpnf & %%~dpnf.exe)
popd %cd%
goto :eof

:clean
echo cleaning
del /s/q *.exe *.obj
goto :eof