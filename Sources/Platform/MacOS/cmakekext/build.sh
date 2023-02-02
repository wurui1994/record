pushd . > /dev/null
export XNU_PATH=/Users/wurui/Documents/BigRepo/Apple_OSS/xnu
cmake -Bbuild -DCMAKE_OSX_DEPLOYMENT_TARGET=$(xcrun --show-sdk-version) -DXNU_PATH=${XNU_PATH}
cmake --build build --target kexthello -v
cd build
sudo rm -rf hello.kext
# codesign --force --deep --sign - kexthello.kext
cp -R kexthello.kext hello.kext
sudo chmod -R 755 hello.kext
sudo chown -R root:wheel hello.kext
# sudo kextload hello.kext
# sudo kextunload hello.kext
popd > /dev/null