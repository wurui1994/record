export LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH=/usr/local/lib
export C_INCLUDE_PATH=/usr/local/include
export CPLUS_INCLUDE_PATH=/usr/local/include
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig

ROOT=$(pwd)

cd $ROOT/zlib
BINARY_PATH=/usr/local/bin \
INCLUDE_PATH=/usr/local/include \
LIBRARY_PATH=/usr/local/lib \
make install -fwin32/Makefile.gcc -j8

cd $ROOT/
bsdtar -xvf SDL2-*.tar.gz
cd SDL2*/
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8
make install

cd $ROOT/
bsdtar -xvf bzip2-*.tar.gz
cd bzip2*/
wget https://github.com/wurui1994/mpv-winbuild-cmake/raw/master/packages/bzip2-1-fixes.patch
patch -p1 -i bzip2-1-fixes.patch
make -j8 install

cd $ROOT/
bsdtar -xvf libiconv-*.tar.gz
cd libiconv*/
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd lame*/
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd xvid*/xvidcore
cd build/generic/
./bootstrap.sh
./configure --prefix=/usr/local
make -j8 install
rm /usr/local/lib/libxvidcore.dll.a /usr/local/bin/libxvidcore.dll

cd $ROOT/
bsdtar -xvf gmp-*.tar.xz
cd gmp*/
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install


cd $ROOT/
cd x265*/source
# comment these lines in CMakeLists.txt:
# list(GET VERSION_LIST 0 X265_VERSION_MAJOR)
# list(GET VERSION_LIST 1 X265_VERSION_MINOR)
# modify this in x264.rc
# FILEVERSION    0,0,0,0
# PRODUCTVERSION 0,0,0,0
cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_SHARED=OFF
make -j8 install

# cd $ROOT/
# cd fontconfig*/
# ./autogen.sh
# ./configure --prefix=/usr/local --enable-static --disable-shared
# make -j8 install

cd $ROOT/
cd harfbuzz*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared --with-icu=no --with-glib=no --with-gobject=no --disable-gtk-doc-html
make -j8 install

cd $ROOT/
cd freetype2*/
# move /usr/include /usr/lib to backup
# cmake -G "MSYS Makefiles" -Bbuild -H. -DCMAKE_INSTALL_PREFIX=/usr/local
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
# cd build
make -j8 install

cd $ROOT/
cd fribidi*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make
make install

cd $ROOT/
cd libass*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

# cd $ROOT/
# cd libbluray*/
# ./bootstrap
# ./configure --prefix=/usr/local --enable-static --disable-shared --disable-bdjava-jar
# make -j8 install

# cd $ROOT/
# cd opencore-amr-code*/
# ./autoconf
# ./configure --prefix=/usr/local --enable-static --disable-shared
# make -j8 install

cd $ROOT/
cd openjpeg*/
# move /usr/include /usr/lib to backup
cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
make -j8 install

cd $ROOT/
cd opus*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd shine*/
./bootstrap
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd snappy*/
cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local
make -j8 install

# cd $ROOT/
# cd soxr-code*/
# cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF
# make -j8 install

cd $ROOT/
cd theora*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd twolame*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd libvpx*/
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd WavPack*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install
rm /usr/local/bin/libwavpack*dll /usr/local/bin/wavpack.exe /usr/local/lib/libwavpack*dll.a /usr/local/bin/wv*.exe

cd $ROOT/
cd libwebp*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd x264*/
./configure --prefix=/usr/local --enable-static
make -j8 install

cd $ROOT/
cd libxml2*/
./autogen.sh
./configure --prefix=/usr/local --enable-static
make -j8 install
# libxml-2.0.pc replace /mingw to /usr/local

cd $ROOT/
cd zimg*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd xz*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd vid.stab*/
# add_library (vidstab STATIC ${SOURCES})
cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local
make -j8 install

cd $ROOT/
cd speex*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

cd $ROOT/
cd aom*/
# move /usr/include /usr/lib to backup
# rm -rf CMakeCache.txt CMakeFiles
cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local -Baom_build -H. -DBUILD_SHARED_LIBS=OFF -DENABLE_EXAMPLES=OFF -DENABLE_DOCS=OFF -DENABLE_TOOLS=OFF -DENABLE_NASM=ON -DCONFIG_UNIT_TESTS=0 -DCMAKE_BUILD_TYPE=Release
cd aom_build
make -j8 install

cd $ROOT/
cd mfx_dispatch*/
autoreconf -i
./configure --prefix=/usr/local --enable-static --disable-shared
# cmake -G "MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/usr/local
make -j8 install

cd $ROOT/
cd vorbis*/
./autogen.sh
./configure --prefix=/usr/local --enable-static --disable-shared
make -j8 install

# msbuild amf

cd $ROOT/
cd nv-codec-headers*/
make -j8 install

wget http://ffmpeg.org/releases/ffmpeg-4.0.1.tar.xz
bsdtar -xvf ffmpeg-4.0.1.tar.xz
cd ffmpeg*

# rm libwinpthread.dll.a libpthread.dll.a libgomp.dll.a libgcc_s.a

./configure --pkg-config-flags=--static --disable-static --enable-shared --enable-gpl --enable-version3 --enable-sdl2 --disable-bzlib --disable-fontconfig --enable-iconv --enable-libass --enable-libfreetype --enable-libmp3lame --enable-libopenjpeg --enable-libopus --enable-libshine --enable-libsnappy --disable-libsoxr --enable-libtheora --disable-libtwolame --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxml2 --enable-libzimg --enable-lzma --enable-zlib --enable-gmp --enable-libvidstab --enable-libvorbis --enable-libspeex --enable-libxvid --enable-libaom --enable-libmfx --enable-ffnvcodec --enable-cuvid --enable-d3d11va --enable-nvenc --enable-nvdec --enable-dxva2 --enable-avisynth

# xmlexports.h add:
# #define LIBXML_STATIC
make -j8

find -name "*.dll"|xargs rm

make -j8 LDFLAGS="-static -Os" install

# find -name "*.dll"|xargs strip
# find -name "*.exe"|xargs strip

# make -j8 LDFLAGS="-static -Os" install DESTDIR=/usr/local/ffmpeg