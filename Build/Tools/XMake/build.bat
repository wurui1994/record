xmake create -l c -P hello
REM cd hello
REM xmake
REM xmake run
xmake run -P hello

xmake create -l c++ -P cpp
xmake run -P cpp

rd /s/q hello cpp