@echo off
set PackageVersion=ffmpeg-4.0-win32
REM bash -c "wget https://github.com/ShiftMediaProject/FFmpeg/releases/download/3.3.5.r89114/libffmpeg_3.3.5.r89114_msvc14.zip"
bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/dev/%PackageVersion%-dev.zip"
bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/shared/%PackageVersion%-shared.zip"
bash -c "wget -c https://github.com/ShiftMediaProject/libass/releases/download/0.14.0-3/libass_0.14.0-3_msvc14.zip"
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

rename avcodec-57.lib avcodec.lib
rename avdevice-57.lib avdevice.lib
rename avfilter-6.lib avfilter.lib
rename avformat-57.lib avformat.lib
rename avutil-55.lib avutil.lib
rename postproc-54.lib postproc.lib
rename swresample-2.lib swresample.lib
rename swscale-4.lib swscale.lib
popd

bash -c "unzip libass_0.14.0-3_msvc14.zip"

copy bin\x86\ass.dll bin\ass.dll
copy lib\x86\ass.lib lib\ass.lib
rmdir /s/q bin\x86
rmdir /s/q bin\x64
rmdir /s/q lib\x86
rmdir /s/q lib\x64
rmdir /s/q licenses

del *.zip
