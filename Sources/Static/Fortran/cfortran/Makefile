CC=gcc
F95=gfortran
main:add.o main.o
	$(F95) -o main add.o main.o
add.o:
	$(F95) -c -o add.o add.f95
main.o:
	$(CC) -c -o main.o main.c

run:
	./main
clean:
	rm *.o *.exe
