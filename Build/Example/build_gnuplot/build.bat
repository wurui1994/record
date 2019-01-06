bash -c "git clone https://git.code.sf.net/p/gnuplot/gnuplot-main gnuplot"
pushd .
cd gnuplot\config\msvc
@call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
set PATH=%PATH%;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;
echo #ifndef GNUPLOT_TIMEBASE_H_INCLUDED >> timestamp.h
echo #define GNUPLOT_TIMEBASE_H_INCLUDED >> timestamp.h
echo const char gnuplot_date[] = "2019-01-05 "; >> timestamp.h
echo #endif /* GNUPLOT_TIMEBASE_H_INCLUDED */ >> timestamp.h
nmake -f Makefile
cd ..\..\demo
..\config\msvc\wgnuplot.exe all.dem
popd