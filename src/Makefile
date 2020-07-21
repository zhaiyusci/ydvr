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

objects=sincdvr.o dvr.o representation.o \
				oscillator.o podvr.o log.o abstract_representation.o \
				md_oscillator.o orthogonal_md_dvr.o orthogonal_md_oscillator.o \
				harmonic.o oscillator_taylor.o \
				md_podvr.o simultaneous_diagonalization.o 

all: libydvr.so libydvr.a

libydvr.so: $(objects)
	$(CXX) -shared -Wl,-soname,libydvr.so -o libydvr.so  $(objects)
libydvr.a: $(objects)
	ar -cvq libydvr.a $(objects)

$(objects): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

$(copes): %.o : %.cc %.h
	$(CXX) -o $@ -c $(CCFLAGS) $< 

.PHONY: clean all 

clean:
	rm -f *.o *.exe *.out *.so
	make -C tests

