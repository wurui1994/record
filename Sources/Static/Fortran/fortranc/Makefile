CC=gcc
F95=gfortran
main:add.o main.o
	$(F95) -o main add.o main.o
add.o: 
	$(CC) -c -o add.o add.c
main.o:
	$(F95) -c -o main.o main.f95

run:
	./main

clean:
	rm *.o *.exe
