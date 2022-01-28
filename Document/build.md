- [Firefox Source Tree Documentation](https://firefox-source-docs.mozilla.org/index.html)
- [TinyCC](https://repo.or.cz/tinycc.git) macOS
```sh
git clone https://repo.or.cz/tinycc.git
mkdir build_tcc binary_tcc
mkdir /usr/local/lib/tcc
../tinycc/configure --prefix=../binary_tcc
time make -j16 install
cp libtcc1.a /usr/local/lib/tcc
export TEMP_INCLUDE_PATH=/Users/wurui/Documents/GitHub/binary_tcc/temp_include
export C_INCLUDE_PATH=${TEMP_INCLUDE_PATH}
export FRAMEWORK_PATH=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks
# support stdarg.h stdbool.h
cp stdarg.h stdbool.h to ${TEMP_INCLUDE_PATH} from dir like /usr/local/opt/gcc/lib/gcc/11/gcc/x86_64-apple-darwin21/11/include
# support opengl 
ln -s ${FRAMEWORK_PATH}/OpenGL.framework/Headers ${TEMP_INCLUDE_PATH}/OpenGL
ln -s ${FRAMEWORK_PATH}/GLUT.framework/Headers ${TEMP_INCLUDE_PATH}/GL
## support opengl native
tcc ${FRAMEWORK_PATH}/GLUT.framework/GLUT.tbd  -lgsl -run gsl_opengl.c 
## support opengl with xquartz
brew install freeglut mesa glfw3
tcc -lglut -lgsl -run gsl_opengl.c 
```