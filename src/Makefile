CXX=g++
EIGENROOT=/usr/local/include/eigen3
CCFLAGS=-Ofast -Wall --std=c++11 -I$(EIGENROOT)\
				-D_YDVR_VERSION="\"Ver. 1.2.0\"" -D_YDVR_YEAR=2019 
LDFLAGS= # -lblas # -llapack

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
