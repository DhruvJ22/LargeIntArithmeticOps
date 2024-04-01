#include <string>
#include <vector>
#include <complex>

#ifndef TYPE_MANIPULATION_H
#define TYPE_MANIPULATION_H

int convertDigitChar2Int(char); // Convert digit representation, char -> int
char convertDigitInt2Char(unsigned int); // Convert digit representation, int -> char

std::vector<int> convertNumStr2Vec(const std::string&);// Convert number representation, str -> vector<int>
std::string convertNumVec2Str(std::vector<int>); // Convert number representation, vector<int> -> str

std::vector<std::complex<double>> convertRealVecInt2VecComplexDouble(std::vector<int>); // Store integer -> real component of complex double
std::vector<int> convertVecComplexDouble2RealVecInt(std::vector<std::complex<double>>); // Store real component of complex double -> integer, assume imaginary == 0

// Helper Functions
std::string removePrecedingZeros(const std::string&); // Remove preceding zeros from string representation of integer
std::vector<int> removePrecedingZeros(std::vector<int>); // Remove preceding zeros from vector<int> representation of integer
std::string computeNumReverseDigits(const std::string&); // Reverse the order of digits in string

#endif