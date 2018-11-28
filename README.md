**To get the code, go to release page on github to get the stable version (v1.0.0).**  Source code in the master branch can be experimental.

# yDVR

A nuclear motion quantum mechanics solver written in C++.

This project is a set of toy codes written in several sundays by [Yu Zhai](http://www.zhaiyusci.net/).

The input is in xml format and no manual is available because it cannot be simpler.  Just follow the `dvr.xml` as a sample.

To run the code, simply `make` and then `ydvr.x <input>`.


The mechanics inside are first run a sinc DVR calculation and then run a PODVR calculation based on the sinc DVR resulting basis kets.

This project is experimental with no warranty.

All code presented here except the xml parser is licensed under Mozilla Public License, Version 2.0.  

Here I thank the [Eigen project](http://eigen.tuxfamily.org/index.php?title=Main_Page) and the [TinyXML-2 project](http://www.grinninglizard.com/tinyxml2/index.html).  I use their code to deal with the matrix and I/O.

Also thank [Prof. Hui Li](http://huiligroup.org/).  He makes me aware that this field is very interesting.

This is my first C++ project and I hope you guys forgive that these codes are not robust enough.
