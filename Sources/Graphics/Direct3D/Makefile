cc=gcc
objects=d3dmain.o
#cflags=-Wl,-subsystem,windows
cflags=-mwindows
clibs=-lwinmm -ld3d9
object:$(objects)
	$(cc) -o main $(objects) $(cflags) $(clibs)
run:
	./main
clean:
	rm main $(objects)
