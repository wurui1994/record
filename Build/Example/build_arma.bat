REM vcpkg install openblas:x64-windows clapack:x64-windows
set CMakePath=D:\Software\GitHub\vcpkg\downloads\cmake-3.9.4-win32-x86\bin
set PATH=%PATH%;%CMakePath%
cmake.exe -Bbuild\debug -H. -DCMAKE_TOOLCHAIN_FILE=D:\Software\GitHub\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=install\debug -A x64

cmake.exe -Bbuild\release -H. -DCMAKE_TOOLCHAIN_FILE=D:\Software\GitHub\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=install -A x64

cmake --build build\debug --target install --config Debug
cmake --build build\release --target install --config Release