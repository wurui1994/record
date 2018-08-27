# brew install libass ffmpeg qt
# git clone https://github.com/wurui1994/QtAV
cd QtAV
mkdir build
cd build

cp -f -R /usr/local/opt/ffmpeg/include .
cp -f -R /usr/local/opt/ffmpeg/lib .

cp -f -R /usr/local/opt/libass/include .
cp -f -R /usr/local/opt/libass/lib .

qmake ../QtAV.pro
make -j8

cp -R lib_osx_x86_64_llvm ../../SubtitleClientProject/build/lib



