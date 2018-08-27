git clone https://github.com/kcat/openal-soft
cd openal-soft
cmake -Bbuild -H. -G "Visual Studio 14 2015"
cd build
msbuild OpenAL.sln /m /p:platform=win32
msbuild OpenAL.sln /m /p:platform=win32 /p:configuration=release
