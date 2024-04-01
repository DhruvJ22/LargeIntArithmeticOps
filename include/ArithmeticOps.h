#include <string>
#include <vector>
#include <complex>

#ifndef ARITHMETIC_OPS_H
#define ARITHMETIC_OPS_H

std::string add(std::string, std::string); // Addition, number1 + number2
std::vector<int> add(std::vector<int>, std::vector<int>); // Addition, number1 + number2

std::string subtract(std::string, std::string); // Subtract, number1 - number2
std::vector<int> subtract(std::vector<int>, std::vector<int>); // Subtract, number1 - number2

std::string mulLong(std::string, std::string); // Long Multiplication
std::vector<int> mulLong(std::vector<int>, std::vector<int>); // Long Multiplication

std::string mulKaratsuba(std::string, std::string); // Karatsuba Multiplication
std::vector<int> mulKaratsuba(std::vector<int>, std::vector<int>); // Karatsuba Multiplication

std::string mulSchonhageStrassen(std::string num1, std::string num2, std::string = "Recursive"); // Schonhage Strassen Multiplication
std::vector<int> mulSchonhageStrassen(std::vector<int>, std::vector<int>, std::string = "Recursive"); // Schonhage Strassen Multiplication
std::vector<int> mulSchonhageStrassenRecursive(std::vector<int>, std::vector<int>); // Schonhage Strassen Multiplication, Recursive
std::vector<int> mulSchonhageStrassenIterative(std::vector<int>, std::vector<int>); // Schonhage Strassen Multiplication, Iterative

std::vector<int> (*selectMultiplyFunction(const std::string&))(std::vector<int>, std::vector<int>);//// To return appropriate `multiplication function` based on the selected `method`; method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"

std::string exponent(std::string base, std::string exponent_val, std::string method = "Long"); // Exponentiation by Squaring
std::vector<int> exponent(std::vector<int> base, std::vector<int> exponent_val, std::string method = "Long"); // Exponentiation by Squaring; method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"

int estimateQuotientDigits(std::vector<int> num1, std::vector<int> num2); // Estimate number of Quotient digits
std::vector<int> divideBy2(std::vector<int> ); // Divide input by 2
std::pair<std::vector<int>, std::vector<int>> computeQuotientRemainder(std::vector<int> numstr1, std::vector<int> numstr2, std::string method = "Long"); // Quotient and Remainder, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"

std::string divide(std::string numstr1, std::string numstr2, std::string method = "Long"); // Divison, wrapper, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"

std::string modulus(std::string numstr1, std::string numstr2, std::string method = "Long"); // Modulus, wrapper, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"

int compareNum1andNum2(std::vector<int> num1, std::vector<int> num2); // Compare the magnitude of two numbers

#endif