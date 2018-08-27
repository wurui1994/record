src := $(shell find ./ -name "*.cc") 
# src := $(shell dir /s/b *.cc) 
objs := $(patsubst %.cc,%.o,$(src))

libcef_wrapper.a: $(objs)
	ar rcs $@ $^
	
libcef_wrapper.so: $(objs)
	gcc -shared -fPIC $@ $^
	
%.o:%.cc
	gcc -I.. -c -o $@ $<

clean:
	rm -f test internal/*.o