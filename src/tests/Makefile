# This file is part of yDVR.
#
# Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

CXX=g++
EIGENROOT=/usr/include/eigen3
CCFLAGS=-g -Ofast -Wall -Wextra --std=c++11 -fPIC -I$(EIGENROOT) -I..
LDFLAGS=-L.. -lydvr
TESTS=harmonic_test.exe sincdvr_test.exe mddvr_test.exe

$(TESTS): %.exe : %.cc
	$(CXX) -o $@ $(CCFLAGS) $< $(LDFLAGS)

tests: $(TESTS)

.PHONY: clean all tests

clean:
	rm -f *.o *.exe *.out *.so

