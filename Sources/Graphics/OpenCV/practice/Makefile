all:main.exe run clean
main.exe:main.o
	$(CXX) -o $@ $< `pkg-config --libs opencv`
main.o:main.cpp
run:
	./main.exe
clean:
	rm *.o *.exe