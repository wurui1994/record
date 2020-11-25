@echo off
REM git.exe clone http://repo.or.cz/tinycc.git 
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
mkdir tcc-binary
pushd .
cd tinycc\win32
REM @call build-tcc.bat -c cl -t 32 -i ..\..\tcc-binary -b ..\..\tcc-binary\tools
call build-tcc.bat -c cl -t 32 -i ..\..\tcc-binary
call build-tcc.bat -clean
popd
cd tcc-binary
tcc -Ilibtcc -L. -ltcc -run examples\libtcc_test.c
pause
REM cls
REM ..\tcc\tcc.exe -DONE_SOURCE -DTCC_TARGET_PE -run tcc.c