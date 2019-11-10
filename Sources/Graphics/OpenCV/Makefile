all:main run clean
main:main.cpp
	clang++ -w -std=c++11 `pkg-config --cflags --libs opencv4` $< -o $@  
main.o:main.cpp
run:
	./main
clean:
	rm main