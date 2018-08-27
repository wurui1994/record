pacman -S mercurial subversion wget git --needed
# wget https://ffmpeg.zeranoe.com/builds/readme/win32/shared/ffmpeg-latest-win32-shared-readme.txt
# hg clone http://hg.libsdl.org/SDL
wget -c https://libsdl.org/release/SDL2-2.0.8.tar.gz
wget -c http://bzip.org/1.0.6/bzip2-1.0.6.tar.gz
wget -c https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.15.tar.gz

svn checkout https://svn.code.sf.net/p/lame/svn/trunk/lame lame
svn checkout http://svn.xvid.org/trunk --username anonymous xvid

# hg clone https://gmplib.org/repo/gmp/
wget -c https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz

# git clone https://gitlab.com/gnutls/gnutls.git
# cd gnutls
# git submodule update --init

cd ..
hg clone https://bitbucket.org/multicoreware/x265

git clone https://github.com/madler/zlib

git clone https://github.com/harfbuzz/harfbuzz
git clone git://anongit.freedesktop.org/fontconfig
git clone git://git.sv.nongnu.org/freetype/freetype2.git
git clone https://github.com/fribidi/fribidi
git clone https://github.com/libass/libass

git clone http://git.videolan.org/git/libbluray.git

git clone https://git.code.sf.net/p/opencore-amr/code opencore-amr-code
git clone https://github.com/uclouvain/openjpeg
git clone https://git.xiph.org/opus.git
git clone https://github.com/savonet/shine
git clone https://github.com/google/snappy
git clone https://git.code.sf.net/p/soxr/code soxr-code
git clone https://git.xiph.org/theora.git
git clone https://github.com/njh/twolame/
git clone https://github.com/webmproject/libvpx
git clone https://github.com/dbry/WavPack
git clone https://github.com/webmproject/libwebp
git clone http://git.videolan.org/git/x264.git

git clone git://git.gnome.org/libxml2
git clone https://github.com/sekrit-twc/zimg
git clone https://git.tukaani.org/xz.git


git clone https://github.com/georgmartius/vid.stab
git clone https://git.xiph.org/vorbis.git
# git clone https://github.com/hoene/libmysofa
git clone https://git.xiph.org/speex.git

git clone https://github.com/GrokStreaming/aom
git clone https://github.com/lu-zero/mfx_dispatch
git clone https://github.com/GPUOpen-LibrariesAndSDKs/AMF
git clone https://git.videolan.org/git/ffmpeg/nv-codec-headers.git
