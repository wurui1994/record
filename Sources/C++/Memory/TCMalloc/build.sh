rm *.heap
g++ hello.cpp -o hello -ltcmalloc
export HEAPPROFILE=$(pwd)/hello
./hello
echo $HEAPPROFILE
pprof hello hello.0001.heap --text