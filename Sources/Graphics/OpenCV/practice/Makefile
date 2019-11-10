# rule
%.exe:%.cpp
	clang++ -w -std=c++11 `pkg-config --cflags --libs opencv4` $< -o $@ 

%.txt:%.exe
	echo 'running22 $<' > $@
	./$<

# set
src := $(shell ls *.cpp) 
objs := $(patsubst %.cpp,%.exe,$(src))
runs := $(patsubst %.cpp,%.txt,$(src))

# target
all: $(objs)
	echo $@ $^

# run
run: $(runs)

# clean
clean:
	rm -f *.exe *.txt