**To get the code, go to release page on github to get the stable version (v1.3.0).**  

# yDVR

A nuclear motion quantum mechanics solver written in C++.

This project is a set of toy codes written in several sundays by [Yu Zhai](http://www.zhaiyusci.net/).

The input is in xml format and no manual is available because it cannot be simpler.  Just follow the `dvr_2001.xml` as a sample.

## Installation

1. The code is simple enough so I did not design a GNU Autotools thing.  
Instead, the Makefile is directly used.
2. You will find some variables in the `src/Makefile`, simply change them:
`CXX`, `EIGENROOT`, `CCFLAGS`.
3. The C++ compiler you use should support the C++11 standard.
As I know, `g++` from version 4.8 should work.
4. The project is based on [Eigen project](http://eigen.tuxfamily.org/index.php?title=Main_Page), 'install' Eigen
before you compiler yDVR.  If you just use the cmake system of Eigen, the `EIGENROOT` should be the same as mine.
For those who do not have a root account, 
you can install Eigen by uncompress the tar.bz2 file in you home directory like this
```sh
$ pwd
/home/yuzhai
$ tar xf ~/Downloads/eigen-3.3.7.tar.bz2 # To uncompress the package you download from Eigen website
$ cd eigen-3.3.7/
$ pwd # The output shoule be used as EIGENROOT in Makefile, which contains `Eigen` directory
/home/yuzhai/eigen-3.3.7
```
5. Eigen is such a beautifully written library so `-O3` should be good for a good performance.

## Running

To run the code, simply `make` and then `./ydvr.x <input>`.  

A sample input file is `src/dvr_2001.xml`.
If not specified, all variables there are in atomic units.  
Supported units are `angstrom`, `cm-1` and `dalton`.

The mechanics inside are first run a sinc DVR calculation and then run a PODVR calculation based on the sinc DVR resulting basis kets.

This project is experimental with no warranty.

All code presented here except the xml parser is licensed under Mozilla Public License, Version 2.0.  

Here I thank the [Eigen project](http://eigen.tuxfamily.org/index.php?title=Main_Page) and the [TinyXML-2 project](http://www.grinninglizard.com/tinyxml2/index.html).  I use their code to deal with the matrix and I/O.

Also thank [Prof. Hui Li](http://huiligroup.org/).  He makes me aware that this field is very interesting.

This is my first C++ project and I hope you guys forgive that these codes are not robust enough.

## Known issues
+ Do not work well with PGI compiler `pgc++ 18.4-0 64-bit target on x86-64 Linux -tp haswell` because the project is based on Eigen.  
As a computational chemist I prefer leave this problem to Eigen development team ;-)

