# This file is part of yDVR.
#
# Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

CXX=g++
EIGENROOT=/usr/include/eigen3
CCFLAGS=-Ofast -Wall --std=c++11 -I$(EIGENROOT) 
LDFLAGS= # -lblas # -llapack

# objects=sincdvr.o podvr.o mathtools.o iotools.o rotation.o tinyxml2/tinyxml2.o 
objects=sincdvr.o discrete_variable_representation.o representation.o \
				oscillator.o podvr.o config.o
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

test.x: sincdvr_test.exe podvr_test.exe

.PHONY: clean all tests

clean:
	rm -f *.o *.exe
