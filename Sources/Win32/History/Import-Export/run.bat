mkdir def mingw msys
cd /d C:\Windows\System32
echo "C:\Windows\System32"
for %%f in (*.dll) do @echo %%~nf && tiny_impdef %%f -o  E:\def\%%~nf.def
cd /d D:\Program\msys2\mingw32\bin
echo "D:\Program\msys2\mingw32\bin"
for %%f in (*.dll) do @tiny_impdef %%f -o  E:\mingw\%%~nf.def
cd /d D:\Program\msys2\usr\bin
echo "D:\Program\msys2\usr\bin"
for %%f in (*.dll) do @tiny_impdef %%f -o  E:\msys\%%~nf.def
pause