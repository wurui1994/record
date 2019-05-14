del *.dll *.exp *.exe *.obj *.lib
REM @pause
cl /c add.c
link /dll /def:add.def add.obj 
cl /c main.c
link main.obj add.lib
main.exe
REM @pause