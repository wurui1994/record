@echo off
set PackageVersion=ffmpeg-4.0.2-win32

bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/dev/%PackageVersion%-dev.zip"
bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/shared/%PackageVersion%-shared.zip"

REM goto :eof

bash -c "unzip %PackageVersion%-dev.zip"
bash -c "unzip %PackageVersion%-shared.zip"

rename %PackageVersion%-dev dev
rename %PackageVersion%-shared shared

move dev/include include
move dev/lib lib
move shared/bin bin

rmdir /s/q dev
rmdir /s/q shared

del lib\*.lib
del lib\*.dll.a
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

pushd %cd%
cd lib 

for %%f in (*.def) do lib /def:%%f

del *.exp *.def

rename avcodec-*.lib avcodec.lib
rename avdevice-*.lib avdevice.lib
rename avfilter-*.lib avfilter.lib
rename avformat-*.lib avformat.lib
rename avutil-*.lib avutil.lib
rename postproc-*.lib postproc.lib
rename swresample-*.lib swresample.lib
rename swscale-*.lib swscale.lib
popd

REM del *.zip
