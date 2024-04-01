#include <iostream>
#include <string>
#include <complex>
#include <vector>
#include <stdexcept>

#include "TypeManipulation.h"

// Convert digit representation, char -> int
int convertDigitChar2Int(char digit_char)
{
    int temp_digit_int = digit_char-'0';

    // Error check
    if (temp_digit_int >= 0 && temp_digit_int <=9)
    {
        return temp_digit_int;
    } 
    else
    {
        throw std::invalid_argument("Invalid input: character '" + std::string(1, digit_char) + "' is not in the range '0' to '9'");    }
}

// Convert digit representation, int -> char
char convertDigitInt2Char(unsigned int digit_int)
{
    if (digit_int < 10)
    {
        return (digit_int+'0');
    }
    else
    {
        throw std::invalid_argument("Invalid input: digit must be between 0 and 9");
    }
}

// Convert number representation, string -> vector<int>
// "5432" -> {2,3,4,5}
std::vector<int> convertNumStr2Vec(const std::string& num)
{
    int num_len = num.length();
    std::vector<int> num_vec(num.length(),0);
    std::string num_reverse = computeNumReverseDigits(num);

    for(int i = 0; i < num_reverse.length(); i++)
    {
        num_vec[i] = convertDigitChar2Int(num_reverse[i]);
    }

    return num_vec;
}

// Convert number representation, vector<int> -> string
// {2,3,4,5} -> "5432"
std::string convertNumVec2Str(std::vector<int> num_vec)
{
    std::string num_str;
 
    for (int i=num_vec.size()-1; i >= 0; --i) {
        num_str = num_str + convertDigitInt2Char(num_vec[i]);
    }

    return num_str;
}

// Store vector<int> as the real component of vector<complex<double>>
std::vector<std::complex<double>> convertRealVecInt2VecComplexDouble(std::vector<int> num_vec)
{
    int len_num_vec = num_vec.size();
    std::vector<std::complex<double>> num_vec_complex(len_num_vec);

    for (int i = 0; i < len_num_vec; i ++)
    {
        if (num_vec[i] >= 0 && num_vec[i] <=9) // Error bounds, num_vec[i] is a digit, not a number
        {
            num_vec_complex[i].real(num_vec[i]*1.0);
            num_vec_complex[i].imag(0.0);
        }
        else
        {
            throw std::invalid_argument("Invalid input: digit must be between 0 and 9");   
        }

    }   

    return num_vec_complex;
}

// Store real components of vector<complex<double>> as vector<int>
std::vector<int> convertVecComplexDouble2RealVecInt(std::vector<std::complex<double>> num12_complex)
{
    int len_num_vec = num12_complex.size();
    std::vector<int> num_vec(len_num_vec);
    int counter = 0 ;

    for (const auto& complex_number : num12_complex) {
        // Check if the real and imaginary parts are numeric
        if (std::isfinite(complex_number.real()) && std::isfinite(complex_number.imag())) {
            int real_part = static_cast<int>(std::round(std::real(complex_number)));
            // Ensure that the real part is non-negative
            // Can be >9, used for FFT and will be fixed through carryAndNormalize()
            if (real_part < 0) {
                throw std::invalid_argument("Real part of the complex number cannot be negative");
            }
            num_vec[counter] = real_part;
            counter++;
        } else {
            // Handle non-numeric values (e.g., throw an exception)
            throw std::invalid_argument("Non-numeric value found in complex number");
        }
    }

    return num_vec;
}

// Removes any preceding zeros of number represented as string
// "001354" -> "1354"
std::string removePrecedingZeros(const std::string& num_orignal)
{    
    int index = 0;
  
    while (num_orignal[index] == '0' && index < num_orignal.length() - 1 ) // Iterate till first non-zero digit
    {
        index ++;
    }  

    return num_orignal.substr(index);
}

// Removes any preceding zeros of number represented as string
// {0,4,5,1,0,0} -> {0,4,5,1}
std::vector<int> removePrecedingZeros(std::vector<int> num_orignal)
{    
    while (num_orignal.back() == 0 && num_orignal.size() > 1 )
    {
        num_orignal.pop_back();
    }
    
    return num_orignal;
}

// Reverses digits of `num`
// "1230" -> "0321"
std::string computeNumReverseDigits(const std::string& num_temp)
{    
    std::string temp_num_reverse;
    int len_num = num_temp.size();

    for(int ind = len_num; ind > 0; ind--)
    {
        temp_num_reverse += num_temp[ind-1];
    }

    return temp_num_reverse; // PRECEDING ZEROS ARE NOT REMOVED
}
