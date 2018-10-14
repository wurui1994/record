# http://nightlies.videolan.org/build/contribs/vlc-contrib-i686-w64-mingw32-latest.tar.bz2
# delete libav*a and libav*dll.a,replace ffmpeg[av*.lib]and 
# libass[ass.lib] if can't work well,
# use vlc\contrib\i686-w64-mingw32\lib\libass.a [and libharfbuzz.a]
# remove libiconv.dll.a, libpthread.dll.a and libwinpthread.dll.a
# modify libav*.pc libass.pc
rm /mingw32/lib/*.dll.a

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
--disable-vulkan \
--disable-libbluray \
--disable-rubberband \
--disable-vapoursynth \
--disable-egl-angle-lib \
--disable-vapoursynth-lazy

./waf build

./waf install --destdir=$(pwd)/package