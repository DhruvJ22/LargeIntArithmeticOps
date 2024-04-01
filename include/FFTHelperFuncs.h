#include <string>
#include <vector>
#include <complex>

#ifndef FFT_HELPER_FUNCS_H
#define FFT_HELPER_FUNCS_H

int padToPowerOf2(std::vector<int>&, int); // Pad vector with 0's for length == power of 2
void computeHermetian(std::vector<std::complex<double>>&); // Compute Hermetian

std::vector<std::complex<double>> digitWiseMul(std::vector<std::complex<double>>, 
                                            std::vector<std::complex<double>> ); // Elementwise Multiplication
void carryAndNormalize(std::vector<int>&, unsigned int);// Normalize by base 10 and propagate the carry value

void fft_radix2_recursive(std::vector<std::complex<double>>&); // FFT Radix-2 Recursive
void fft_radix2_iterative(std::vector<std::complex<double>>&); // FFT Radix-2 Iterative
std::vector<std::complex<double>> computeFFT(std::vector<std::complex<double>>, std::string = "Recursive"); // FFT wrapper, Choose and call FFT Radix-2 Recursive/Iterative based on method

std::vector<int> computeInvFFT(std::vector<std::complex<double>>, std::string = "Recursive"); // Inverse FFT, Hermetian -> FFT -> divide by length -> Alter data type

#endif