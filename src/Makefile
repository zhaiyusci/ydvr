CXX=g++
EIGENROOT=/usr/include/eigen3
CCFLAGS=-Ofast -Wall --std=c++11 -I$(EIGENROOT) \
				-D__YDVR_SCALAR__=float \
				-D_YDVR_VERSION="\"Ver. 2.0.0\"" -D_YDVR_YEAR=2020 
LDFLAGS= # -lblas # -llapack

# objects=sincdvr.o podvr.o mathtools.o iotools.o rotation.o tinyxml2/tinyxml2.o 
objects=sincdvr.o discrete_variable_representation.o representation.o \
				oscillator.o podvr.o
copes=co_pes_2016/ELJ.o 

sincdvr_test.exe: $(objects) $(copes) sincdvr_test.cc
	$(CXX) -o $@ $(CCFLAGS) sincdvr_test.cc $(objects) $(copes)

podvr_test.exe: $(objects) $(copes) podvr_test.cc
	$(CXX) -o $@ $(CCFLAGS) podvr_test.cc $(objects) $(copes)

$(objects): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

$(copes): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

all: ydvr.x

test.x: test.o $(objects)
	$(CXX) -o $@ $(CCFLAGS) test.o $(objects)


ydvr.o: ydvr.cc mathtools.o
	$(CXX) -o $@ -c $(CCFLAGS) ydvr.cc

ydvr.x: ydvr.o $(objects)
	$(CXX) -o $@ $(CCFLAGS) ydvr.o $(objects) $(LDFLAGS)

.PHONY: clean all

clean:
	rm -f *.o *.x
