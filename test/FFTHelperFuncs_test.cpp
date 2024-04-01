#include <string>
#include <complex>
#include <fftw3.h>

#include <gtest/gtest.h>
#include "FFTHelperFuncs.h"

// Comparison function for vectors of complex numbers
bool compareComplexVectors(const std::vector<std::complex<double>>& vec1, const std::vector<std::complex<double>>& vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        if (abs(std::real(vec1[i])-std::real(vec2[i])) > 1e-10 || abs(std::imag(vec1[i])-std::imag(vec2[i])) > 1e-10 ) {
            return false;
        }
    }
    return true;
}

// int padToPowerOf2(std::vector<int>& num_vec, int len_num12);
TEST(FFTHelperFuncsTest, padToPowerOf2Test) {
    
    std::vector<int> input1 = {0,0,1};
    int pow2len = padToPowerOf2(input1, 5);
    EXPECT_EQ(input1, (std::vector<int>{0,0,1,0,0,0,0,0}));

    std::vector<int> input2 = {3,2,1};
    pow2len = padToPowerOf2(input2, 4);
    EXPECT_EQ(input2, (std::vector<int>{3,2,1,0}));

    std::vector<int> input3 = {3,2,1,0,1};
    pow2len = padToPowerOf2(input3, 13);
    EXPECT_EQ(input3, (std::vector<int>{3,2,1,0,1,0,0,0,0,0,0,0,0,0,0,0}));

    std::vector<int> input4 = {3,2,1,0,1};
    EXPECT_THROW(padToPowerOf2(input4, 3), std::invalid_argument);
}


// void computeHermetian(std::vector<std::complex<double>>&);
TEST(FFTHelperFuncsTest, computeHermetianTest){

    std::vector<std::complex<double>> input1 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(2.0, 1.0),
                                                std::complex<double>(2.0, -1.0)};
    std::vector<std::complex<double>> expected_output1 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, -1.0),
                                            std::complex<double>(2.0, 1.0)};
    computeHermetian(input1);
    EXPECT_EQ(input1, expected_output1);

    std::vector<std::complex<double>> input2 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(3.0, 1.0),
                                                std::complex<double>(4.0, 2.0),
                                                std::complex<double>(4.0, -2.0),
                                                std::complex<double>(4.0, -1.0)};
    std::vector<std::complex<double>> expected_output2 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(3.0, -1.0),
                                                std::complex<double>(4.0, -2.0),
                                                std::complex<double>(4.0, 2.0),
                                                std::complex<double>(4.0, 1.0)};
    computeHermetian(input2);
    EXPECT_EQ(input2, expected_output2);
}


// std::vector<std::complex<double>> digitWiseMul(std::vector<std::complex<double>>, std::vector<std::complex<double>>);
TEST(FFTHelperFuncsTest, digitWiseMulTest){

    std::vector<std::complex<double>> input11 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 1.0),
                                            std::complex<double>(2.0, -1.0)};
    std::vector<std::complex<double>> input12 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(2.0, 1.0),
                                                std::complex<double>(2.0, -1.0)};
    std::vector<std::complex<double>> expected_output1 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(3.0, 4.0),
                                                std::complex<double>(3.0, -4.0)};
    EXPECT_EQ(digitWiseMul(input11, input12), expected_output1);
    

    std::vector<std::complex<double>> input21 = {std::complex<double>(1.0, 2.0),
                                            std::complex<double>(2.0, -1.0),
                                            std::complex<double>(2.0, 1.0)};
    std::vector<std::complex<double>> input22 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(2.0, 1.0),
                                                std::complex<double>(2.0, -1.0)};
    std::vector<std::complex<double>> expected_output2 = {std::complex<double>(1.0, 2.0),
                                                std::complex<double>(5.0, 0.0),
                                                std::complex<double>(5.0, 0.0)};
    EXPECT_EQ(digitWiseMul(input21, input22), expected_output2);
}


// void carryAndNormalize(std::vector<int>& result, unsigned int base);
TEST(FFTHelperFuncsTest, carryAndNormalizeTest){

    std::vector<int> input1 = {11,12,13,8};
    carryAndNormalize(input1, 10);
    EXPECT_EQ(input1, (std::vector<int>{1,3,4,9}));

    std::vector<int> input2 = {0,1212,1,2};
    carryAndNormalize(input2, 10);
    EXPECT_EQ(input2, (std::vector<int>{0,2,2,4,1}));
}


// void fft_radix2_recursive(std::vector<std::complex<double>>& num_vec);
TEST(FFTHelperFuncsTest, fft_radix2_recursiveTest){

    std::vector<std::complex<double>> input1 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(3.0, 0.0)};
    EXPECT_THROW(fft_radix2_recursive(input1), std::invalid_argument);
    
    // Test against fft_radix2_iterative
    std::vector<std::complex<double>> input21 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(3.0, 0.0),
                                            std::complex<double>(4.0, 0.0)};
    std::vector<std::complex<double>> input22 = input21;
    fft_radix2_recursive(input21);
    fft_radix2_iterative(input22);
    EXPECT_TRUE(compareComplexVectors(input21, input22));

    // Test against known values
    std::vector<std::complex<double>> input3 = {std::complex<double>(9.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(8.0, 0.0),
                                            std::complex<double>(3.0, 0.0)};
    std::vector<std::complex<double>> expected_output3 = {std::complex<double>(22.0, 0.0),
                                            std::complex<double>(1.0, 1.0),
                                            std::complex<double>(12.0, 0.0),
                                            std::complex<double>(1.0, -1.0)};
    fft_radix2_recursive(input3);
    EXPECT_TRUE(compareComplexVectors(input3, expected_output3));
}


// void fft_radix2_iterative(std::vector<std::complex<double>>& num_vec);
TEST(FFTHelperFuncsTest, fft_radix2_iterativeTest){

    std::vector<std::complex<double>> input1 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(3.0, 0.0)};
    EXPECT_THROW(fft_radix2_iterative(input1), std::invalid_argument);
    
    // Test against fft_radix2_recursive
    std::vector<std::complex<double>> input21 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(3.0, 0.0),
                                            std::complex<double>(4.0, 0.0)};
    std::vector<std::complex<double>> input22 = input21;
    fft_radix2_iterative(input21);
    fft_radix2_recursive(input22);
    EXPECT_TRUE(compareComplexVectors(input21, input22));

    // Test against known values
    std::vector<std::complex<double>> input3 = {std::complex<double>(9.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(8.0, 0.0),
                                            std::complex<double>(3.0, 0.0)};
    std::vector<std::complex<double>> expected_output3 = {std::complex<double>(22.0, 0.0),
                                            std::complex<double>(1.0, 1.0),
                                            std::complex<double>(12.0, 0.0),
                                            std::complex<double>(1.0, -1.0)};
    fft_radix2_iterative(input3);
    EXPECT_TRUE(compareComplexVectors(input3, expected_output3));
}

// std::vector<std::complex<double>> computeFFT(std::vector<std::complex<double>>, std::string);
TEST(FFTHelperFuncsTest, computeFFT2Test){

    // Check incorrect `method`
    std::vector<std::complex<double>> input1 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(2.0, 0.0),
                                                std::complex<double>(3.0, 0.0)};
    EXPECT_THROW(computeFFT(input1, "JustGiveMeFFT"), std::invalid_argument);

    // Check FFT Recursive
    std::vector<std::complex<double>> input2 = {std::complex<double>(9.0, 0.0),
                                                std::complex<double>(2.0, 0.0),
                                                std::complex<double>(8.0, 0.0),
                                                std::complex<double>(3.0, 0.0)};
    std::vector<std::complex<double>> input2copy = input2;
    std::vector<std::complex<double>> expected_output2 = {std::complex<double>(22.0, 0.0),
                                            std::complex<double>(1.0, 1.0),
                                            std::complex<double>(12.0, 0.0),
                                            std::complex<double>(1.0, -1.0)};
    fft_radix2_recursive(input2copy);
    EXPECT_TRUE(compareComplexVectors(computeFFT(input2, "Recursive"),input2copy));

    // Check FFT Iterative
    std::vector<std::complex<double>> input3copy = input2;
    fft_radix2_iterative(input3copy);
    EXPECT_TRUE(compareComplexVectors(computeFFT(input2, "Iterative"),input3copy));

    // Test against fftw3
    std::vector<std::complex<double>> input4 = {std::complex<double>(1.0, 0.0),
                                            std::complex<double>(2.0, 0.0),
                                            std::complex<double>(3.0, 0.0),
                                            std::complex<double>(4.0, 0.0)};
    int len_num_vec = input4.size();
    std::vector<std::complex<double>> expected_output4;

    fftw_complex* in = new fftw_complex[len_num_vec];
    fftw_complex* out = new fftw_complex[len_num_vec];
    fftw_plan p = fftw_plan_dft_1d(len_num_vec, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    // Convert digits to complex numbers
    for (int i = 0; i < len_num_vec; ++i)
    {
        in[i][0] = std::real(input4[i]);
        in[i][1] = std::imag(input4[i]);
    }
    // Execute FFT
    fftw_execute(p);
    // Convert results to vector<complex<double>>    
    for (int i = 0; i < len_num_vec; i ++)
    {
        expected_output4.push_back(std::complex<double>{out[i][0],out[i][1]});
    }
    // Cleanup
    fftw_destroy_plan(p);
    delete[] in;
    delete[] out;

    EXPECT_TRUE(compareComplexVectors(computeFFT(input4), expected_output4));
}


// std::vector<int> computeInvFFT(std::vector<std::complex<double>> num12_complex, std::string method)
TEST(FFTHelperFuncsTest, computeInvFFTTest){

    // Test against fftw3
    std::vector<std::complex<double>> input1 = {std::complex<double>(10.0, 0.0),
                                            std::complex<double>(-2.0, 2.0),
                                            std::complex<double>(-2.0, 0.0),
                                            std::complex<double>(-2.0, -2.0)};
    int len_num_vec = input1.size();
    std::vector<int> expected_output1;

    fftw_complex* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len_num_vec);
    double* out = (double*) fftw_malloc(sizeof(double) * len_num_vec);

    // Initialize input array with complex numbers (example)
    for (int i = 0; i < len_num_vec; ++i)
    {
        in[i][0] = std::real(input1[i]); // Real part
        in[i][1] = std::imag(input1[i]); // Imaginary part
    }

    // Create plan for IFFT
    fftw_plan plan = fftw_plan_dft_c2r_1d(len_num_vec, in, out, FFTW_ESTIMATE);

    // Execute the plan
    fftw_execute(plan);
    
    for (int i = 0; i < len_num_vec; i ++)
    {
        expected_output1.push_back(std::round(out[i]/len_num_vec));
    }

    // Free memory and destroy the plan
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    EXPECT_EQ(computeInvFFT(input1), expected_output1);


    // Check incorrect `method`
    std::vector<std::complex<double>> input2 = {std::complex<double>(1.0, 0.0),
                                                std::complex<double>(2.0, 0.0),
                                                std::complex<double>(3.0, 0.0)};
    EXPECT_THROW(computeInvFFT(input2, "JustGiveMeFFT"), std::invalid_argument);
}