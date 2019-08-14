objects=sincdvr.o podvr.o mathtools.o iotools.o rotation.o tinyxml2/tinyxml2.o 
# Using LLVM
# CCFLAG= -Ofast -Ieigen -Wall --std=c++1z
# CXX=clang++-8

# Using GCC
CCFLAG= -Ofast -Ieigen -Wall --std=c++1z 
CXX=g++-8

all: ydvr.x

test.x: test.o $(objects)
	$(CXX) -o $@ $(CCFLAG) test.o $(objects)

$(objects): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAG) $< 

ydvr.o: ydvr.cc mathtools.o
	$(CXX) -c -o $@ $(CCFLAG) ydvr.cc

ydvr.x: ydvr.o $(objects)
	$(CXX) -o $@ $(CCFLAG) ydvr.o $(objects)

.PHONY: clean all

clean:
	rm -f *.o *.x
