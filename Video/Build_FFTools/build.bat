REM https://git.ffmpeg.org/gitweb/ffmpeg.git/tree/refs/heads/release/3.4:/fftools
REM wget https://github.com/ShiftMediaProject/SDL/releases/download/release-2.0.8/libsdl_release-2.0.8_msvc14.zip
@call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
set INCLUDE=%INCLUDE%;E:\Company\pc\SubtitleClientProject\src\include;E:\GitHub\misc\Video\Build_FFTools\libsdl\include\SDL;
set LIB=%LIB%;E:\Company\pc\SubtitleClientProject\src\lib;E:\GitHub\misc\Video\Build_FFTools\libsdl\lib\x86;
cl /w ffmpeg.c cmdutils.c ffmpeg_hw.c ffmpeg_opt.c ffmpeg_filter.c ffmpeg_cuvid.c avutil.lib avresample.lib avformat.lib avcodec.lib swresample.lib avdevice.lib avfilter.lib swscale.lib postproc.lib Shell32.lib

cl /w ffplay.c cmdutils.c avutil.lib avresample.lib avformat.lib avcodec.lib swresample.lib avdevice.lib avfilter.lib swscale.lib postproc.lib Shell32.lib sdl2.lib