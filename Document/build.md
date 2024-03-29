- [Firefox Source Tree Documentation](https://firefox-source-docs.mozilla.org/index.html)
- [TinyCC](https://repo.or.cz/tinycc.git) macOS
```sh
git clone https://repo.or.cz/tinycc.git
mkdir build_tcc binary_tcc
cd build_tcc
../tinycc/configure --prefix=$(pwd)/../binary_tcc
time make -j16
time make -j16 install
# For M1 arm64 `ln -s /opt/homebrew/include /usr/local/include` `ln -s /opt/homebrew/lib /usr/local/lib`
export TEMP_INCLUDE_PATH=$HOME/Documents/GitHub/binary_tcc/temp_include
export C_INCLUDE_PATH=${TEMP_INCLUDE_PATH}:$HOMEBREW_PREFIX/include
export LIBRARY_PATH=$HOMEBREW_PREFIX/lib
export FRAMEWORK_PATH=$(xcrun --show-sdk-path)/System/Library/Frameworks
# support stdarg.h stdbool.h
# cp stdarg.h stdbool.h to ${TEMP_INCLUDE_PATH} from dir like /Library/Developer/CommandLineTools/usr/include/c++/v1
# support opengl 
mkdir -p ${TEMP_INCLUDE_PATH}
ln -s ${FRAMEWORK_PATH}/OpenGL.framework/Headers ${TEMP_INCLUDE_PATH}/OpenGL
# ln -s ${FRAMEWORK_PATH}/GLUT.framework/Headers ${TEMP_INCLUDE_PATH}/GL
sudo ln -s $(xcrun --show-sdk-path)/System/Library/Frameworks/GLUT.framework/Headers $(xcrun --show-sdk-path)/usr/include/GL
## support opengl native
tcc ${FRAMEWORK_PATH}/GLUT.framework/GLUT.tbd -lgsl -run gsl_opengl.c 
## support opengl with xquartz
brew install freeglut mesa glfw3
tcc -lglut -lgsl -run gsl_opengl.c 
```