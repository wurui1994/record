git clone https://github.com/ninja-build/ninja
pushd .
cd ninja
mkdir obj_unix
cd obj_unix
g++ -w -c ../src/*.cc ../src/*.cc
rm *test.o *in.o hash_collision_bench.o
cd ..
g++ obj_unix/*.o -o ninja
./ninja -t list
popd
