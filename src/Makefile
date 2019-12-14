CXX=g++
CCFLAGS= -Ofast -Ieigen -Wall --std=c++1z -D_YDVR_VERSION="\"Ver. 1.2.0\"" -D_YDVR_YEAR=2019# -fopenmp -DEIGEN_DONT_PARALLELIZE -DEIGEN_USE_BLAS -DEIGEN_USE_LAPACK 
LDFLAGS= # -lblas -llapack

objects=sincdvr.o podvr.o mathtools.o iotools.o rotation.o tinyxml2/tinyxml2.o 

all: ydvr.x

test.x: test.o $(objects)
	$(CXX) -o $@ $(CCFLAGS) test.o $(objects)

$(objects): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

ydvr.o: ydvr.cc mathtools.o
	$(CXX) -o $@ -c $(CCFLAGS) ydvr.cc

ydvr.x: ydvr.o $(objects)
	$(CXX) -o $@ $(CCFLAGS) ydvr.o $(objects) $(LDFLAGS)

.PHONY: clean all

clean:
	rm -f *.o *.x
