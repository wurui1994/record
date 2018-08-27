bash -c "wget -c https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.9/5.9.5/single/qt-everywhere-opensource-src-5.9.5.zip"

bash -c "tar -xvf qt-everywhere-opensource-src-5.9.5.zip"

REM @call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

set PATH=%PATH%;D:\Software\vcpkg\downloads\tools\jom\jom-1.1.2;C:\Python27;
REM E:\GitHub\Google\depot_tools\win_tools-2_7_6_bin\python\bin;

cd qt-everywhere-opensource-src-5.9.4
REM configure -proprietary-codecs -opensource -confirm-license -nomake examples -nomake tests -release
REM option `-debug-and-release` (Apple and Windows only)
configure.bat -proprietary-codecs -opensource -confirm-license -nomake examples -nomake tests -release

REM jom /j32 module-qtwebengine

REM Fix for Windows
REM Fix 1: std::max/std::min --> using std::max;max(a,b);[For file `windows.h`]
REM Fix 2: use unix2dos to deal with `unicode problem` for MSVC

REM Qt5 Compile:

REM ioutils.cpp: Line 106
REM // Q_ASSERT(isAbsolutePath(baseDir));

REM For QtWebEngine [ Qt < 5.10]:
REM UTF-8-BOM index_rect.h spiral_iterator.h reverse_spiral_iterator.h gpu_image_decode_controller.cc