export PackageVersion=ffmpeg-3.4.1-macos64
wget -c https://ffmpeg.zeranoe.com/builds/macos64/dev/$PackageVersion-dev.zip
wget -c https://ffmpeg.zeranoe.com/builds/macos64/shared/$PackageVersion-shared.zip

unzip $PackageVersion-dev.zip
unzip $PackageVersion-shared.zip

mv $PackageVersion-dev dev
mv $PackageVersion-shared shared

mv dev/include include
mv shared/bin bin
mkdir lib
cp bin/*.dylib lib/


pushd .
ROOT=$(pwd)
git clone https://github.com/fribidi/fribidi
git clone https://github.com/libass/libass
cd $ROOT/fribidi
./bootstrap && ./configure --enable-static=yes --enable-shared=no --prefix=$(pwd)/../install
make -j1 && make install
cd $ROOT/libass
./autogen.sh
./configure --disable-shared --prefix=$(pwd)/../install
make -j$(nproc --all) && make install
popd

cp -R install .