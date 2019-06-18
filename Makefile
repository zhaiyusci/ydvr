objects=sincdvr.o podvr.o mathtools.o tinyxml2.o 
# # Using LLVM
# CCFLAG= -Ieigen -fopenmp -Wall --std=c++14
# CXX=clang++-6.0

# Using GCC
CCFLAG= -Ieigen -fopenmp -Wall --std=c++14 
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
