- [Firefox Source Tree Documentation](https://firefox-source-docs.mozilla.org/index.html)
- [TinyCC](https://repo.or.cz/tinycc.git) macOS
```sh
git clone https://repo.or.cz/tinycc.git
mkdir build_tcc binary_tcc
cd build_tcc
../tinycc/configure --prefix=$(pwd)/../binary_tcc
time make -j16 install
# For M1 arm64 `ln -s /opt/homebrew/include /usr/local/include` `ln -s /opt/homebrew/lib /usr/local/lib`
export TEMP_INCLUDE_PATH=/Users/wurui/Documents/GitHub/binary_tcc/temp_include
export C_INCLUDE_PATH=${TEMP_INCLUDE_PATH}
export FRAMEWORK_PATH=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks
# support stdarg.h stdbool.h
# cp stdarg.h stdbool.h to ${TEMP_INCLUDE_PATH} from dir like /Library/Developer/CommandLineTools/usr/include/c++/v1
# support opengl 
mkdir -p ${TEMP_INCLUDE_PATH}
ln -s ${FRAMEWORK_PATH}/OpenGL.framework/Headers ${TEMP_INCLUDE_PATH}/OpenGL
ln -s ${FRAMEWORK_PATH}/GLUT.framework/Headers ${TEMP_INCLUDE_PATH}/GL
## support opengl native
tcc ${FRAMEWORK_PATH}/GLUT.framework/GLUT.tbd  -lgsl -run gsl_opengl.c 
## support opengl with xquartz
brew install freeglut mesa glfw3
tcc -lglut -lgsl -run gsl_opengl.c 
```