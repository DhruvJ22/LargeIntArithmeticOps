#include <string>
#include <vector>
#include <complex>

#include "TypeManipulation.h"

// Pad 0's to num_vec to be of length = len_num12, prepare num_vec for FFT
// Note: Initiially, num_vec.size() != len_num12, in most cases
int padToPowerOf2(std::vector<int>& num_vec, int len_num12)
{
    if (len_num12 < num_vec.size())
    {
        throw std::invalid_argument("Length of input vector cannot be less than input length");   
    }

    int powOf2 = 1;
    // Get the exponent to 2 that exceeds the number of digits
    while (powOf2 < len_num12)
    {
        powOf2 *= 2;
    }

    // Pad zeros to make the number of digits a power of 2
    num_vec.resize(powOf2,  0);

    return powOf2;
}

// Hermetian, flip sign of imag components
void computeHermetian(std::vector<std::complex<double>>& num_vec_complex)
{
    int len_num_vec = num_vec_complex.size();
    for (int i = 1; i < len_num_vec; i++)
    {
        num_vec_complex[i].imag(-std::imag(num_vec_complex[i]));
    }
}

// Elementwise multiplication of complex numbers
std::vector<std::complex<double>> digitWiseMul(std::vector<std::complex<double>> num1, 
                                                                        std::vector<std::complex<double>> num2)
{
    int len_num1 = num1.size();
    std::vector<std::complex<double>> num12_vec(len_num1);

    // Multiply complex numbers at same vector index
    for(int i=0; i<len_num1; i++)
    {
        num12_vec[i] = num1[i] * num2[i];
    }

    return num12_vec;
}

// Normalize by specified `base` and propagate the carry value
void carryAndNormalize(std::vector<int>& result, unsigned int base) {

    int carry = 0;

    // Iterate through the digits from right to left
    for (int i = 0; i <=result.size() - 1; i++) {

        if (result[i] < 0)
        {
            throw std::invalid_argument("Vector elements cannot be negative");
        }
        
        result[i] += carry; // Add carry from previous iteration

        // Perform carrying operation if the digit is out of range
        if (result[i] < 0 || result[i] >= base) {
            carry = result[i] / base; // Calculate carry
            result[i] %= base; // Update digit value
        } else {
            carry = 0; // Reset carry
        }
    }

    // If there's a carry after the last iteration, add a new digit
    if (carry != 0) {
        result.push_back(carry);
    }
}


// FFT Radix-2, Cooley-Tucker, Recursive approach
void fft_radix2_recursive(std::vector<std::complex<double>>& num_vec)
{
    int len_num_vec = num_vec.size();
    int half_len = len_num_vec / 2;

    // Base case: single element (no need for further processing)
    if (len_num_vec <= 1) return;

    // Check if size is even (required for radix-2)
    if (len_num_vec % 2 != 0) 
    {
        throw std::invalid_argument("Input size must be a power of 2, to correct pad number with zeros");
    }

    // Divide into even and odd sub-arrays
    std::vector<std::complex<double>> even(half_len), odd(half_len);
    for (int i = 0; i < half_len; ++i)
    {
        even[i] = num_vec[2*i];
        odd[i] = num_vec[2*i + 1];
    }

    // Recursive calls for sub-arrays
    fft_radix2_recursive(even);
    fft_radix2_recursive(odd);

    // Butterfly operations (similar to iterative approach)
    double theta = -2.0 * M_PI / len_num_vec, theta_i = 0.0;
    for (int i = 0; i < half_len; ++i) 
    {
        theta_i = theta * i;
        std::complex<double> w (cos(theta_i), sin(theta_i));
        
        num_vec[i] = even[i] + w * odd[i];
        num_vec[i + half_len] = even[i] - w * odd[i];
    }
}

// FFT Radix-2, Cooley-Tucker, Iterative approach
void fft_radix2_iterative(std::vector<std::complex<double>>& num_vec)
{
    int len_num_vec = num_vec.size();
    int half_len = len_num_vec / 2;

    // Check if size is even (required for radix-2)
    if (len_num_vec % 2 != 0) 
    {
        throw std::invalid_argument("Input size must be a power of 2, to correct pad number with zeros");
    }
    
    std::vector<std::complex<double>> even(half_len), odd(half_len);
    
    // Divide into even and odd sub-arrays
    for (int i = 0; i < half_len; ++i)
    {
        even[i] = num_vec[2*i];
        odd[i] = num_vec[2*i + 1];
    }

    for(int k = 0; k < half_len; k++)
    {
        std::complex<double> Ek (0,0), Ok (0,0);
        for(int m = 0; m < half_len; m++)
        {
            std::complex<double> t = std::polar(1.0, -2 * M_PI * m * k / half_len);
            Ek += even[m] * t;
            Ok += odd[m] * t;
        }
    
        // Butterfly operations
        std::complex<double> twiddle_factor = std::polar(1.0, -2 * M_PI * k / len_num_vec);
        num_vec[k] = Ek + twiddle_factor * Ok;
        num_vec[k + half_len] = Ek - twiddle_factor * Ok;
    }
}


// Compute FFT, wrapper around fft_radix2_recursive() and fft_radix2_iterative()
std::vector<std::complex<double>> computeFFT(std::vector<std::complex<double>> num_vec_complex, std::string method)
{
    if (method.compare("Recursive") == 0)
    {
        fft_radix2_recursive(num_vec_complex);
    }
    else if (method.compare("Iterative") == 0)
    {
        fft_radix2_iterative(num_vec_complex);
    }
    else
    {
        throw std::invalid_argument("Incorrect method, options are Recursive or Iterative");
    }   

    return num_vec_complex;
}


// Compute Inverse FFT, Hermetian -> FFT -> Divide by length -> Alter data type
std::vector<int> computeInvFFT(std::vector<std::complex<double>> num12_complex, std::string method)
{
    int len_num_vec = num12_complex.size(); 
    std::vector<int> num12_ifft(len_num_vec);

    // Compute Hermetian
    computeHermetian(num12_complex);

    // Choose and compute fft Radix-2
    num12_complex = computeFFT(num12_complex, method);
    
    // Divide by length
    for (int i = 0; i < len_num_vec; ++i)
    {        
        num12_complex[i].real(std::real(num12_complex[i])/len_num_vec);         
    }

    // Change data type
    num12_ifft = convertVecComplexDouble2RealVecInt(num12_complex);

    return num12_ifft;
}
