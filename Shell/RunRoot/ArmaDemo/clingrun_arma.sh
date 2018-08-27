cling -larmadillo -Dmain=example example.cpp
# root -e ".L /usr/lib/libarmadillo.so" -q -l -b example.cpp -e "main()" 
rm A.txt
cling -larmadillo -Dmain=save_ppm save_ppm.cpp

cling -lSDL -lSDL_image -larmadillo -Dmain=save_ppm save_ppm.cpp