# Large Integer Arithmetic Operations

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Description

This repository contains a collection of C++ functions for efficiently performing arithmetic operations on large integers. The functions are designed to handle positive integers with hundreds of thousands of digits. The programs comprise robust error checks, bound checks and unit tests.

### Implemented Operations:

- Addition
- Subtraction
- Multiplication (Four different implementations):
  - Long multiplication
  - Karatsuba algorithm
  - Schonhadge-Strassen algorithm (using Cooley Tucker, radix-2, Recursive)
  - Schonhadge-Strassen algorithm (using Cooley Tucker, radix-2, Iterative)
- Division (using binary search)
- Modulus (using binary search)
- Exponentiation (using Exponentiation by Squaring)
- Fast Fourier Transform (FFT) and Inverse Fast Fourier Transform (IFFT)

***The core implementations of the operations are performed on `std::vector<int>` representation of base-10 integers.***

## Requirements

- C++11 or higher
- [Compiler](https://gcc.gnu.org/) with C++ support
- FFTW 3.3.10 (for unit testing)
- Google Test (for unit testing, installed as a submodule)

## Installation

Clone the repository to your local machine:

```bash
git clone git@github.com:DhruvJ22/LargeIntArithmeticOps.git
``

Compile the source files using your preferred C++ compiler:
```
cd LargeIntArithmeticOps
mkdir build && cd build
cmake ..
make
```

## Key Files
1. ***TypeManipulation.cpp***: This file contains functions for handling type manipulations, such as converting between different data types, manipulating complex numbers, and managing large integer representations. Some of the functions included in this file are:-
- convertDigitChar2Int: Converts a character representing a digit to an integer.
- convertNumStr2Vec: Converts a string representing a large integer to a vector of integers.
- Other functions for type conversions and manipulations.

2. ***FFTHelperFuncs.cpp***: This file houses functions related to Fast Fourier Transform (FFT) and Inverse Fast Fourier Transform (IFFT). It includes implementations of FFT algorithms for efficiently computing the Fourier transform of large data sets. Some of the functions included in this file are:
- computeHermetian: Compute Hermetian of complex numbers.
- fft_radix2_recursive: Compute FFT using Radix-2 recursively.
- Other FFT-related functions and utilities.

3. ***ArithmeticOperations.cpp***: This file contains implementations of arithmetic operations on large integers, including addition, subtraction, multiplication, division, modulus operations, and exponentiation. Additionally, it provides wrappers and utility functions for accessing and utilizing these arithmetic operations seamlessly. Some of the functions included in this file are:
- add: Performs addition of large integers.
- subtract: Performs subtraction of large integers.
- exponent: Performs exponentiation by squaring of large integers with specified multiplication algorithms (e.g., Long multiplication, Karatsuba algorithm, etc.).
- Other arithmetic operations and utility functions.

## Unit Tests

The repository includes various unit tests implemented using Google Test (as a submodule) to ensure the correctness of the arithmetic operations, as well as showcase the robustness of the programs. Additionally, the FFT and IFFT implementations are tested against "fftw3" library. You can run the tests by building the project and executing the tests binary (`./tests`).

## Examples

There are two examples (`./example1`, `./example2`) as well as a _Menu-driven Calculator_ (`./main`) to illustrate the capabilities of the programs.

## Contributing

Contributions are welcome! Please feel free to fork the repository and submit pull requests to contribute new features, improvements, or bug fixes.

## References

1. https://www.csc.kth.se/utbildning/kth/kurser/DD2440/avalg07/algnotes.pdf
2. http://www.allisons.org/ll/AlgDS/Arithmetic/SandS/
