#include <string>
#include <complex>

#include <gtest/gtest.h>
#include "TypeManipulation.h"

// int convertDigitChar2Int(char digit_char);
TEST(TypeManipulationTest, convertDigitChar2IntTest_ValidInputs) {

    EXPECT_EQ(convertDigitChar2Int('0'), 0) << "Test failed for '0'";
    EXPECT_EQ(convertDigitChar2Int('2'), 2) << "Test failed for '2'";
    EXPECT_EQ(convertDigitChar2Int('9'), 9) << "Test failed for '9'";
}
TEST(TypeManipulationTest, convertDigitChar2IntTest2_InvalidInputs) {

    EXPECT_THROW(convertDigitChar2Int('-'), std::invalid_argument) << "Test failed for '-'";
    EXPECT_THROW(convertDigitChar2Int('.'), std::invalid_argument) << "Test failed for '.'";
    EXPECT_THROW(convertDigitChar2Int('e'), std::invalid_argument) << "Test failed for 'e'";
}

// char convertDigitInt2Char(int digit_int);
TEST(TypeManipulationTest, convertDigitInt2Char_ValidInputs) {

    EXPECT_EQ(convertDigitInt2Char(1), '1') << "Test failed for 1" ;
    EXPECT_EQ(convertDigitInt2Char(2), '2') << "Test failed for 2";
    EXPECT_EQ(convertDigitInt2Char(9), '9') << "Test failed for 9";
}
TEST(TypeManipulationTest, convertDigitInt2Char_InvalidInputs) {

    EXPECT_THROW(convertDigitInt2Char(-1), std::invalid_argument) << "Test failed for -1";
    EXPECT_THROW(convertDigitInt2Char(12), std::invalid_argument) << "Test failed for 12";
    EXPECT_THROW(convertDigitInt2Char(100), std::invalid_argument) << "Test failed for 100";
}

// std::vector<int> convertNumStr2Vec(const std::string& num)
TEST(TypeManipulationTest, convertNumStr2Vec_ValidInputs) {

    std::vector<int> expected_output1 = {};
    EXPECT_EQ(convertNumStr2Vec(""), expected_output1);

    std::vector<int> expected_output2 = {5};
    EXPECT_EQ(convertNumStr2Vec("5"), expected_output2);

    std::vector<int> expected_output3 = {1, 2, 3, 4, 5};
    EXPECT_EQ(convertNumStr2Vec("54321"), expected_output3);
}
TEST(TypeManipulationTest, convertNumStr2Vec_InvalidInputs) {

    EXPECT_THROW(convertNumStr2Vec("-123.5"), std::invalid_argument);
    EXPECT_THROW(convertNumStr2Vec("1e10"), std::invalid_argument);
    EXPECT_THROW(convertNumStr2Vec("22/7"), std::invalid_argument);
}


// std::string convertNumVecr2Str(std::vector<int> num_vec)
TEST(TypeManipulationTest, convertNumVecr2Str_ValidInputs) {

    std::vector<int> input1 = {};
    EXPECT_EQ(convertNumVec2Str(input1), "");

    std::vector<int> input2 = {5};
    EXPECT_EQ(convertNumVec2Str(input2), "5");

    std::vector<int> input3 = {1,2,3,4,5};
    EXPECT_EQ(convertNumVec2Str(input3), "54321");
}

TEST(TypeManipulationTest, convertNumVecr2Str_InvalidInputs) {

    std::vector<int> input1 = {-1};
    EXPECT_THROW(convertNumVec2Str(input1), std::invalid_argument);

    std::vector<int> input3 = {26,7,-1};
    EXPECT_THROW(convertNumVec2Str(input3), std::invalid_argument);
}


// std::vector<std::complex<double>> convertRealInt2ComplexDouble(std::vector<int>);
TEST(TypeManipulationTest, convertRealVecInt2VecComplexDouble_ValidInputs) {

    std::vector<std::complex<double>> expected_output1 = {std::complex<double>(1.0, 0.0)};
    EXPECT_EQ(convertRealVecInt2VecComplexDouble({1}), expected_output1);

    std::vector<std::complex<double>> expected_output2 = {std::complex<double>(1.0, 0.0),
                                                          std::complex<double>(2.0, 0.0),
                                                          std::complex<double>(5.0, 0)};
    EXPECT_EQ(convertRealVecInt2VecComplexDouble({1, 2, 5}), expected_output2);
}
TEST(TypeManipulationTest, convertRealVecInt2VecComplexDouble_InvalidInputs) {

   // Should be 0<=Digit<=9 
    EXPECT_THROW(convertRealVecInt2VecComplexDouble({'h','i'}), std::invalid_argument);
    EXPECT_THROW(convertRealVecInt2VecComplexDouble({-1}), std::invalid_argument);
    EXPECT_THROW(convertRealVecInt2VecComplexDouble({0,356}), std::invalid_argument);
}


// std::vector<int> convertVecComplexDouble2RealVecInt(std::vector<std::complex<double>> num12_complex)
TEST(TypeManipulationTest, convertVecComplexDouble2RealVecInt_ValidInputs) {

    std::vector<std::complex<double>> input1 = {std::complex<double>(1.0, 1.0)};
    EXPECT_EQ(convertVecComplexDouble2RealVecInt(input1), (std::vector<int>{1}));

    std::vector<std::complex<double>> input2 = {std::complex<double>(5.65, 0.1),
                                                          std::complex<double>(25.0, 0.3),
                                                          std::complex<double>(1.0, 0)};
    EXPECT_EQ(convertVecComplexDouble2RealVecInt(input2), (std::vector<int>{6, 25, 1}));
}
TEST(TypeManipulationTest, convertVecComplexDouble2RealVecInt_InvalidInputs) {

    std::vector<std::complex<double>> input1 = {std::complex<double>(-1.0, 1.2)};
    EXPECT_THROW(convertVecComplexDouble2RealVecInt(input1), std::invalid_argument);    
}


// std::string removePrecedingZeros(const std::string& num_orignal)
TEST(TypeManipulationTest, removePrecedingZerosString_ValidInputs) {

    EXPECT_EQ(removePrecedingZeros("00000000000000000000000000254643434"), "254643434");
    EXPECT_EQ(removePrecedingZeros("00"), "0");
    EXPECT_EQ(removePrecedingZeros("12"), "12");
    EXPECT_EQ(removePrecedingZeros("0-123"), "-123");
    EXPECT_EQ(removePrecedingZeros("12300"), "12300");
    EXPECT_EQ(removePrecedingZeros("Oh000h"), "Oh000h");
}


// std::vector<int> removePrecedingZeros(std::vector<int> num_orignal)
TEST(TypeManipulationTest, removePrecedingZerosInt_ValidInputs) {

    EXPECT_EQ(removePrecedingZeros(std::vector<int>{0,0,0,0,0,1}), (std::vector<int>{0,0,0,0,0,1})); // 100000
    EXPECT_EQ(removePrecedingZeros(std::vector<int>{1,0,0,0,0,0}), (std::vector<int>{1})); // 1
    EXPECT_EQ(removePrecedingZeros(std::vector<int>{0,0,1,2,3,0,0,0}), (std::vector<int>{0,0,1,2,3})); // 321
}

// std::string computeNumReverseDigits(const std::string& num_temp)
TEST(TypeManipulationTest, computeNumReverseDigits_ValidInputs) {

    EXPECT_EQ(computeNumReverseDigits("1122"), "2211");
    EXPECT_EQ(computeNumReverseDigits("-533-"), "-335-");
    EXPECT_EQ(computeNumReverseDigits("1456.21"), "12.6541");
}

