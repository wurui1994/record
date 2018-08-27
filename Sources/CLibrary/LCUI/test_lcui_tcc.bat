REM @echo off
bash -c "wget -c https://github.com/lc-soft/LCUI/releases/download/v1.0-beta/LCUI-1.0-beta-for-windows.x86.zip"
bash -c "unzip LCUI-1.0-beta-for-windows.x86.zip"
bash -c "cd LCUI-1.0-beta-for-windows.x86 && unzip LCUI.v1.0.0-beta.zip"
bash -c "cd LCUI-1.0-beta-for-windows.x86/LCUI && find ./include -name "*.h"|xargs dos2unix"
bash -c "cd LCUI-1.0-beta-for-windows.x86/LCUI.v1.0.0-beta/test && dos2unix helloworld.c"

pushd .
cd LCUI-1.0-beta-for-windows.x86
set INCLUDE=%cd%\LCUI\include
set BINPATH=%cd%\LCUI\bin\Release
set PATH=E:\GitHub\Console\tcc-0.9.27;%BINPATH%
cd LCUI.v1.0.0-beta\test 
tcc -I%INCLUDE% -L%BINPATH% -lLCUI -run helloworld.c
popd