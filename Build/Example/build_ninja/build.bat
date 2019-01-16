git clone https://github.com/ninja-build/ninja
cd ninja
@call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
mkdir obj_win
REM for /f %%f in ('dir /b src\*.cc *.c') do @cl /nologo /c /w /EHsc src\%%f /Fo.\obj_win\
cl /nologo /c /w /EHsc src\*.cc src\*.c /Fo.\obj_win\
del .\obj_win\*test.obj .\obj_win\*.in.obj .\obj_win\hash_collision_bench.obj
cl .\obj_win\*.obj /Fe:ninja.exe
ninja.exe -t list
REM rd /s/q .\obj_win