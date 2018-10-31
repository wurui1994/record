# http://nightlies.videolan.org/build/contribs/vlc-contrib-i686-w64-mingw32-latest.tar.bz2
# bsdtar -xvf vlc-contrib-i686-w64-mingw32-latest.tar.bz2 i686-w64-mingw32/lib/libharfbuzz.a i686-w64-mingw32/lib/libfreetype.a i686-w64-mingw32/lib/libfribidi.a i686-w64-mingw32/lib/libass.a

# remove libav*a and libav*dll.a
# remove libiconv.dll.a, libpthread.dll.a and libwinpthread.dll.a

# replace these libs:
# ffmpeg[av*.lib] and libass[ass.lib] as well as libass's dependencies,
# [libharfbuzz.a libfreetype.a libfribidi.a]
# use vlc\contrib\i686-w64-mingw32\lib\libass.a

# modify libav*.pc libass.pc [Libs.private:]

# ./waf configure 
# Comment out this line [wscript] 'deps': 'ffmpeg || libav' 
# ./waf configure
# Option: comment out function `print_libav_versions` in player/main.c

# https://mirrors.tuna.tsinghua.edu.cn/help/msys2/
# autorebase.bat
# pacman -Syyu
# pacman -S mingw-w64-i686-toolchain
# makepkg-mingw -sLf
# cd src/mpv*/
# /d/GitHub/Record/Video/Build_MPV

rm /mingw32/lib/*.dll.a
rm /mingw32/i686-w64-mingw32/lib/*.dll.a
# rm /mingw32/i686-w64-mingw32/lib/*pthread*.dll.a

# ./bootstrap.py
# git clone https://github.com/mpv-player/mpv
# cd mpv


DEST_OS=win32 \
TARGET=${MINGW_CHOST} \
PKG_CONFIG=/usr/bin/pkg-config \
CC=gcc PERL=/usr/bin/perl \
AR=${MINGW_PREFIX}/bin/ar \
WINDRES=${MINGW_PREFIX}/bin/windres \
RST2MAN=${MINGW_PREFIX}/bin/rst2man3 \
/usr/bin/python3 ./waf configure LDFLAGS="-static -Os" \
--prefix=${MINGW_PREFIX} \
--check-c-compiler=gcc \
--enable-libmpv-shared \
--enable-static-build \
--enable-lua \
--enable-sdl2 \
--enable-caca \
--enable-cdda \
--enable-jpeg \
--enable-lcms2 \
--enable-libass \
--enable-dvdnav \
--enable-dvdread \
--enable-uchardet \
--enable-egl-angle \
--enable-libarchive \
--disable-aom \
--disable-vulkan \
--disable-libbluray \
--disable-rubberband \
--disable-vapoursynth \
--disable-egl-angle-lib \
--disable-vapoursynth-lazy

./waf build

./waf install --destdir=$(pwd)/package

pushd .
cd $(pwd)/package/mingw32/bin
strip *.com *.exe *.dll
popd