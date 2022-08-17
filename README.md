# PiRATe
**Pi Randomness Assessment Test (PiRATe)** is a comprehensive software package for evaluation of Random Number Generators (RNGs) using various statistical tests including **DIEHARDER**, **NIST SP800-22**, **NIST SP800-90B**, **ENT**, **Borel Normality**, and **Chaitin-Schwartz-Solovay-Strassen (CSSS)** tests.
**PiRATe** offers an easy-to-use graphical user interface (GUI) to perform all tests in a single environment.

## Tests
All tests employed in this software are listed in the table below:

| Test		      | Ref.						    		                                |
|-----------------|-------------------------------------------------------------------------|
| DIEHARDER       | https://webhome.phy.duke.edu/~rgb/General/dieharder.php 		        |
| NIST SP800-22   | https://github.com/greendow/A-variant-of-NIST-SP-800-22-test-suit	    |
| NIST SP800-90B  | https://github.com/usnistgov/SP800-90B_EntropyAssessment		        |
| ENT		      | https://www.fourmilab.ch/random/					                    |
| Borel Normality | https://zenodo.org/record/4440318					                    |
| CSSS		      | https://zenodo.org/record/4440318					                    |


## Dependencies
C++ (>= 17),
qt6 (>= 6.3),
cmake (>= 3.14),
libgl-dev,
libgmp-dev,
libdivsufsort-dev,
libbz2-dev,
libjsoncpp-dev,
libssl-dev,
libmpfr-dev,
libts-dev,
libjasper,
libmng-dev,
libmd4c-dev,
libdouble-conversion-dev,
libb2-dev,
libicu-dev,
libpcre2-dev,
dieharder


## How to compile
To avoid incompatibilities, it is recommended to re-compile the codes in the `Tests/` directory before compiling **PiRATe**.

For NIST SP800-22:
```
make -f Makefile_for_linux.txt
```

For NIST SP800-90B:
```
make iid
make non_iid
```

For ENT:
```
make
```

For CSSS3:
```
g++ -O2 SS_Test3_Carm.cpp -o SS_Test3_Carm -lgmp -lgmpxx
g++ -O2 SS_Test3_Carm_BitFlip.cpp -o SS_Test3_Carm_BitFlip -lgmp -lgmpxx
g++ -O2 SS_Test3_Carm_Verbose.cpp -o SS_Test3_Carm_Verbose -lgmp -lgmpxx
g++ -O2 SS_Test3_Carm_Verbose_BitFlip.cpp -o SS_Test3_Carm_Verbose_BitFlip -lgmp -lgmpxx
```


To compile **PiRATe**, go to the software source directory, then enter the below commands in terminal:

```
mkdir build
cp -r Tests ./build/
cmake -S . -B ./build/
cd ./build
make
```

Now you see an executable file in `build/` directory. 
