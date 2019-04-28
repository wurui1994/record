git clone https://github.com/skui-org/skia --depth 1
@pushd .
@call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86
@popd
cd skia
REM 注释掉:
REM # png expat zlib gif jpeg-turbo
REM # src/ports/SkFontMgr_custom.cpp
REM # src/ports/SkFontMgr_custom_directory.cpp
REM # src/codec/SkSampledCodec.cpp
cmake -H. -Bbuild -DCMAKE_EXE_LINKER_FLAGS=/machine:x86 -DSKIA_SHARED=1
cd build 
msbuild /m /p:configuration=release /p:platform=win32 skia.sln
REM cmake --build build --target skia -- /m /p:configuration=release /p:platform=win32