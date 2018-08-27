rmdir /s/q build
REM del *.exe *.txt *.cmake
cmake -Bbuild -H. -G "MSYS Makefiles"
cd build
make
hello
cd ..