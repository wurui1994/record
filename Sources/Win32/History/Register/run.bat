reg add HKCU\Environment /f /v MSYS /d D:\Program\msys2\mingw32\bin;D:\Program\msys2\usr\tcc 
reg add HKCU\Environment /f /v Path /t REG_EXPAND_SZ /d %%MSYS%%

reg query HKCU\Environment
path
pause
