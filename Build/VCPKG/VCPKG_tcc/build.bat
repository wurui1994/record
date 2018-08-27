@echo off
REM git.exe clone http://repo.or.cz/tinycc.git 
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat""
mkdir tcc-0.9.27
pushd .
cd tinycc\win32
REM @call build-tcc.bat -c cl -t 32 -i ..\..\tcc-0.9.27 -b ..\..\tcc-0.9.27\tools
call build-tcc.bat -c cl -t 32 -i ..\..\tcc-0.9.27
call build-tcc.bat -clean
popd
cd tcc-0.9.27
tcc -Ilibtcc -L. -ltcc -run examples\libtcc_test.c
pause
REM cls
REM ..\tcc\tcc.exe -DONE_SOURCE -DTCC_TARGET_PE -run tcc.c