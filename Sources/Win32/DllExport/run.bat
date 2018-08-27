@del *.dll *.exp *.exe *.obj *.lib
@pause
@cl /c add.cpp
@link /dll /def:add.def add.obj /libpath:"C:\Program Files (x86)\Microsoft Visual Studio\VC98\Lib"
@cl /c main.cpp
@link main.obj add.lib  /libpath:"C:\Program Files (x86)\Microsoft Visual Studio\VC98\Lib"
@main.exe
@pause