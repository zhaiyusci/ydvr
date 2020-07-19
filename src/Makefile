# This file is part of yDVR.
#
# Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

CXX=g++
EIGENROOT=/usr/include/eigen3
CCFLAGS=-g -Ofast -Wall -Wextra --std=c++11 -fPIC -I$(EIGENROOT) 
LDFLAGS= # -lblas # -llapack

# objects=sincdvr.o podvr.o mathtools.o iotools.o rotation.o tinyxml2/tinyxml2.o 
objects=sincdvr.o dvr.o representation.o \
				oscillator.o podvr.o log.o abstract_representation.o \
				md_oscillator.o orthogonal_md_dvr.o orthogonal_md_oscillator.o \
				harmonic.o oscillator_taylor.o \
				md_podvr.o simultaneous_diagonalization.o 

copes=co_pes_2016/ELJ.o 


libydvr.so: $(objects)
	$(CXX) -shared -Wl,-soname,libydvr.so -o libydvr.so  $(objects)

podvr_test.exe: libydvr.so $(copes) podvr_test.cc
	$(CXX) -o $@ $(CCFLAGS) podvr_test.cc $(copes) -L. -lydvr

harmonic_test.exe: libydvr.so $(copes) harmonic_test.cc
	$(CXX) -o $@ $(CCFLAGS) harmonic_test.cc $(copes) -L. -lydvr

sincdvr_test.exe: $(objects) $(copes) sincdvr_test.cc
	$(CXX) -o $@ $(CCFLAGS) sincdvr_test.cc $(objects) $(copes)

mddvr_test.exe: libydvr.so mddvr_test.cc ../contrib/simultaneousDiagonalization/simultaneousDiagonalization.o
	$(CXX) -o $@ $(CCFLAGS) mddvr_test.cc -L. -lydvr 

$(objects): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

$(copes): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

all: ydvr.x

tests: sincdvr_test.exe podvr_test.exe mddvr_test.exe harmonic_test.exe

.PHONY: clean all tests

clean:
	rm -f *.o *.exe *.out *.so

