#include <string>
#include <complex>
#include <vector>
#include <functional>

#include "ArithmeticOps.h"
#include "FFTHelperFuncs.h"
#include "TypeManipulation.h"


// Function: numvec1 + numvec2
std::string add(std::string numstr1, std::string numstr2)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(add(num1, num2));
}
// Function: numvec1 + numvec2
std::vector<int> add(std::vector<int> num1, std::vector<int> num2)
{
    // Error Check
    num1 = convertNumStr2Vec(convertNumVec2Str(num1));
    num2 = convertNumStr2Vec(convertNumVec2Str(num2)); 

    int num1_len = num1.size(), num2_len = num2.size();

    // Swap if num2 has extra digit(s)
    if (num2_len > num1_len)
    {
        std::vector<int> temp = num1;
        num1 = num2;
        num2 = temp;

        int temp_len = num1_len;
        num1_len = num2_len;
        num2_len = temp_len;
    }

    num1.push_back(0); // Extend length by 1, to store possible carry value

    std::vector<int> result (num1_len >= num2_len ? num1_len+1 : num2_len + 1, 0);   

    int next_digit = 0;
    int carry_val = 0, digitwise_sum = 0;
    int num1_ind = 0;
    
    // Digitwise add and propagate carry value, for number of digits in num2
    for(int num2_ind = 0; num2_ind <= num2_len - 1; num2_ind++)
    {
        digitwise_sum = num1[num1_ind] + num2[num2_ind];
        carry_val = digitwise_sum/10;
        digitwise_sum = digitwise_sum%10;
        result[num1_ind] = digitwise_sum;

        int count = 1;
        while(carry_val == 1)
        {
            next_digit = num1[num1_ind+count];
            
            if (next_digit == 9)
            {
                num1[num1_ind+count] = 0;                
                count++;
            }
            else
            {
                num1[num1_ind+count] = next_digit + carry_val;      
                carry_val = 0;          
            }            
        }
        num1_ind++;
    }

    // Store digits of num1 to result that are beyond the number of digits in num2
    while (num1_ind<=num1_len)
    {
        result[num1_ind] = num1[num1_ind];
        num1_ind++;
    }

    return removePrecedingZeros(result);
}

// Function: numvec1 - numvec2
std::string subtract(std::string numstr1, std::string numstr2)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(subtract(num1, num2));
}

// Function: numvec1 - numvec2
// Assumes: num1 > num2
std::vector<int> subtract(std::vector<int> num1, std::vector<int> num2)
{
    // Error Check
    num1 = convertNumStr2Vec(convertNumVec2Str(num1));
    num2 = convertNumStr2Vec(convertNumVec2Str(num2)); 

    int compare_num1_num2_val = compareNum1andNum2(num1, num2);
    if (compare_num1_num2_val == -1)
    { 
        throw std::invalid_argument("Num1 needs to ge be greater than Num2, only compatible with positive integers.");
    }
    else if (compare_num1_num2_val == 0)
    {
        return (std::vector<int>{0});
    }

    int num1_len = num1.size(), num2_len = num2.size();    
    std::vector<int> result (num1.size(), 0);   

    int num1_digit = 0, num2_digit = 0;
    int next_digit = 0;
    int borrow_val = 0, digitwise_diff = 0;

    int num1_ind = 0;
    
    // Digitwise subtract and propagate borrow value, for number of digits in num2
    for(int num2_ind = 0; num2_ind < num2_len; num2_ind++)
    {
        if (num1[num1_ind] >= num2[num2_ind])
        {
            digitwise_diff = num1[num1_ind]-num2[num2_ind]; // Perform digitwise subtraction
            borrow_val = 0;
        }
        else
        {
            digitwise_diff = 10+num1[num1_ind]-num2[num2_ind]; 
            borrow_val = 1;
        }

        result[num1_ind] = digitwise_diff;

        int count = 1;
        while(borrow_val == 1)
        {
            next_digit = num1[num1_ind+count];
            
            if (next_digit == 0)
            {
                num1[num1_ind + count] = 9;                
                count++;
            }
            else
            {
                num1[num1_ind + count] = next_digit - borrow_val;      
                borrow_val = 0;          
            }            
        }

        num1_ind++;
    }

    // Store digits of num1 to result that are beyond the number of digits in num2
    while (num1_ind < num1_len)
    {        
        result[num1_ind] = num1[num1_ind];
        num1_ind++;
    }    

    return removePrecedingZeros(result);
}

// Function: numvec1 * numvec2, Long Multiplication
std::string mulLong(std::string numstr1, std::string numstr2)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(mulLong(num1, num2));
}

// Function: numvec1 * numvec2, Long Multiplication
std::vector<int> mulLong(std::vector<int> num1, std::vector<int> num2)
{     
    // Error Check
    num1 = convertNumStr2Vec(convertNumVec2Str(num1));
    num2 = convertNumStr2Vec(convertNumVec2Str(num2)); 

    int num_digit_index = 0;
    int num1_len = num1.size(), num2_len = num2.size();

    int current_digit = 0, next_digit = 0;
    int carry_val = 0, remain_val = 0, digitwise_mul = 0;

    // Define `result` to store the result of num1 * num2
    int result_len = num1_len+num2_len;
    std::vector<int> result (result_len, 0);
    int result_ind = 0;

    // Digitwise multiplication and propagation of carry value
    for(int num1_ind = 0;  num1_ind < num1_len; num1_ind++)
    {    
        result_ind = num_digit_index;

        for(int num2_ind = 0; num2_ind < num2_len; num2_ind++)
        {    
            digitwise_mul = num1[num1_ind]*num2[num2_ind]; // Perform digitwise multiplication

            carry_val = digitwise_mul/10; // Compute the 'current' carry over value
            remain_val = digitwise_mul%10; // Compute the 'current' remaining value
            
            current_digit = result[result_ind];
            next_digit = result[result_ind+1];

            // Modify the current and next digit based on the remaining and carry over values
            // Order of operations is important!
            current_digit = current_digit + remain_val;
            next_digit = next_digit + carry_val + current_digit/10; 
            current_digit = current_digit%10;

            result[result_ind] = current_digit;
            result[result_ind+1] = next_digit;

            result_ind++;
        }
        num_digit_index++;
    }

    return removePrecedingZeros(result);
}


// Function: numvec1 * numvec2, Karatsuba Algorithm
std::string mulKaratsuba(std::string numstr1, std::string numstr2)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(mulKaratsuba(num1, num2));
}

// Function: numvec1 * numvec2, Karatsuba Algorithm
// Use of recursion and call backs after breaking multiple times, base case -> single digit
std::vector<int> mulKaratsuba(std::vector<int> num1, std::vector<int> num2)
{
    // Error Check
    num1 = convertNumStr2Vec(convertNumVec2Str(num1));
    num2 = convertNumStr2Vec(convertNumVec2Str(num2)); 

    int num1_len = num1.size(), num2_len = num2.size();    
    std::vector<int> a(num1_len/2), b(num1_len/2), c(num2_len/2), d(num2_len/2);
    std::vector<int> aMULc, bMULd, aSUMb, cSUMd, aSUMb_MUL_cSUMd, interm_term;
    
    if (num1_len == 1 || num2_len)
    {
        return mulLong(num1, num2);
    }

    // Break num1 and num2 into 2 parts, e.g.: "1524" -> "15" + "24" 
    // => "num1" = "a" + "b", "num2" = "c" + "d"
    // => "num1 * num2" =  "a * c" + "(a + b)*(c + d) - b * d - a * c"  + "b * d"
    std::copy(num1.begin(), num1.begin() + num1_len/2, a.begin());
    std::copy(num1.rbegin() + num1_len/2, num1.rend(), b.begin());

    std::copy(num2.begin(), num2.begin() + num2_len/2, c.begin());
    std::copy(num2.rbegin() + num2_len/2, num2.rend(), d.begin());

    aMULc = mulKaratsuba(a, c);
    bMULd = mulKaratsuba(b, d);

    aSUMb = add(a, b);
    cSUMd = add(c, d);
    aSUMb_MUL_cSUMd = mulKaratsuba(aSUMb, cSUMd);

    interm_term = subtract(subtract(aSUMb_MUL_cSUMd, bMULd), aMULc);

    std::vector<int> result(bMULd.size() + interm_term.size() + aMULc.size());
    for (int i = 0; i < bMULd.size(); i++) result[i] = bMULd[i];
    for (int i = 0; i < interm_term.size(); i++) result[i + bMULd.size()] = interm_term[i];
    for (int i = 0; i < aMULc.size(); i++) result[i + interm_term.size() + bMULd.size()] = aMULc[i];
    
    return removePrecedingZeros(result);
}

// Function: numvec1 * numvec2, Schonhage-Strassen Algorithm
std::string mulSchonhageStrassen(std::string numstr1, std::string numstr2, std::string method)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(mulSchonhageStrassen(num1, num2, method));
}

// Function: numvec1 * numvec2, Schonhage-Strassen Algorithm Recursive
std::vector<int> mulSchonhageStrassenRecursive(std::vector<int> numvec1, std::vector<int> numvec2)
{   
    return mulSchonhageStrassen(numvec1, numvec2, "Recursive");
}

// Function: numvec1 * numvec2, Schonhage-Strassen Algorithm Iterative
std::vector<int> mulSchonhageStrassenIterative(std::vector<int> numvec1, std::vector<int> numvec2)
{   
    return mulSchonhageStrassen(numvec1, numvec2, "Iterative");
}

// Function: numvec1 * numvec2, Schonhage-Strassen Algorithm (Recursive or Iterative)
std::vector<int> mulSchonhageStrassen(std::vector<int> numvec1, std::vector<int> numvec2, std::string method)
{
    // Error Check
    numvec1 = convertNumStr2Vec(convertNumVec2Str(numvec1));
    numvec2 = convertNumStr2Vec(convertNumVec2Str(numvec2)); 

    int len_num1 = numvec1.size(), len_num2 = numvec2.size();
    int len_num12 = len_num1+len_num2;
  
    // Pad with Zeros
    len_num12 = padToPowerOf2(numvec1, len_num12);
    len_num12 = padToPowerOf2(numvec2, len_num12);

    std::vector<std::complex<double>> num1_fft(len_num12), num2_fft(len_num12), num12(len_num12), numveccomplex1, numveccomplex2;
    std::vector<int> result(len_num12);

    // Compute FFT of digits
    numveccomplex1 = convertRealVecInt2VecComplexDouble(numvec1);
    num1_fft = computeFFT(numveccomplex1, method);
    numveccomplex2 = convertRealVecInt2VecComplexDouble(numvec2);
    num2_fft = computeFFT(numveccomplex2, method); 

    // Digitwise multiplication of Fourier coefficientts
    num12 = digitWiseMul(num1_fft, num2_fft);

    // Compute IFFT of Fourier coefficients
    result = computeInvFFT(num12, method);

    // carryANDNormalize by base 10
    carryAndNormalize(result, 10);

    return removePrecedingZeros(result);
}

// To return appropriate `multiplication function` based on the selected `method`, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::vector<int> (*selectMultiplyFunction(const std::string& method))(std::vector<int>, std::vector<int>) {
    if (method == "Long")
    {
        return mulLong;
    }
    else if (method == "Karatsuba") 
    {
        return mulKaratsuba;
    }
    else if (method == "SchonhadgeStrassenRecursive")
    {
        return mulSchonhageStrassenRecursive;
    }
    else if (method == "SchonhadgeStrassenIterative")
    {
        return mulSchonhageStrassenIterative;
    }
    else 
    {
        throw std::invalid_argument("Incorrect method, options are: Long, Karatsuba, SchonhadgeStrassenRecursive or SchonhadgeStrassenIterative");   
    }
}


// Function: base ^ exponent_val, Exponentiation by Squaring, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::string exponent(std::string numstr1, std::string numstr2, std::string method)
{
    std::vector<int> num1 = convertNumStr2Vec(numstr1);
    std::vector<int> num2 = convertNumStr2Vec(numstr2);

    return convertNumVec2Str(exponent(num1, num2, method));
}

// Function: base ^ exponent_val, Exponentiation by Squaring, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::vector<int> exponent(std::vector<int> base, std::vector<int> exponent_val, std::string method)
{
    // Error Check
    base = convertNumStr2Vec(convertNumVec2Str(base));
    exponent_val = convertNumStr2Vec(convertNumVec2Str(exponent_val)); 

    std::vector<int> result = {1};
    std::vector<int> (*multiplyFunc_ptr)(std::vector<int>, std::vector<int>) = selectMultiplyFunction(method);

    if (compareNum1andNum2(exponent_val, {0}) == 0) // Case: base ^ 0
    {
        return {1};
    }
    else if (compareNum1andNum2(exponent_val, {1}) == 0)// Case: base ^ 1
    {
        return base;
    }
    else// Case: base ^ exponent, exponent > 1
    {
        // Exponentiation by Squaring
        while (compareNum1andNum2(exponent_val, {0}) == 1)
        {
            if (exponent_val[0]%2 == 0) // exponent is Even, base ^ 2
            {
                base = multiplyFunc_ptr(base, base);
                exponent_val = divideBy2(exponent_val);
            }
            else{
                result = multiplyFunc_ptr(result, base); // exponent is Odd, result * base
                exponent_val = subtract(exponent_val, {1});
            }
        }
    }
    return result;
}

// Function to estimate the number of digits in the quotient
int estimateQuotientDigits(std::vector<int> num1, std::vector<int> num2) 
{
    // Error Check
    num1 = convertNumStr2Vec(convertNumVec2Str(num1));
    num2 = convertNumStr2Vec(convertNumVec2Str(num2)); 

    int num1_digits = num1.size(), num2_digits = num2.size();

    // Check: num1 > num2
    if (num1_digits >= num2_digits)
    {
      return (num1_digits - num2_digits + 1);
    }
    else
    {
        throw std::invalid_argument("Invalid input: digits of num1 needs to be more than num2");   
    }
}

// Function: num/2
std::vector<int> divideBy2(std::vector<int> num)
{
    // Error Check
    num = convertNumStr2Vec(convertNumVec2Str(num));

    std::vector<int> quotient(num.size());
    int borrow=0;

    for(int i = num.size()-1; i >= 0; --i)
    { 
        quotient[i] = (borrow * 10 + num[i]) / 2;
        borrow = (num[i]) % 2;
    }
    
    return quotient;
}

// Compute Quotient and Remainder, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::pair<std::vector<int>, std::vector<int>> computeQuotientRemainder(std::vector<int> dividend, std::vector<int> divisor, std::string method)
{
    // Error Check
    dividend = convertNumStr2Vec(convertNumVec2Str(dividend));
    divisor = convertNumStr2Vec(convertNumVec2Str(divisor)); 

    std::vector<int> (*multiplyFunc_ptr)(std::vector<int>, std::vector<int>) = selectMultiplyFunction(method);

    // CHECK: num1 > num2, else quotient = 0
    int compare_Dvidend_Divisor_val = compareNum1andNum2(dividend, divisor);

    if (compare_Dvidend_Divisor_val == -1)
    { 
        return std::make_pair(std::vector<int>{0}, dividend);
    }
    else if (compare_Dvidend_Divisor_val == 0)
    {
        return std::make_pair(std::vector<int>{1}, std::vector<int>{0});
    }
    else if (compareNum1andNum2(divisor, {0}) == 0)
    {
        throw std::invalid_argument("Invalid input: Dividend caanot be divided by 0.");
    }
    
    // Get max quotient, set min quotient, max if  100 and 999 then max will be 10
    int q_est = estimateQuotientDigits(dividend, divisor);
    std::vector<int> minQout ={1}, maxQout(q_est);
    maxQout.push_back(1);
    
    std::vector<int> currentQuotient = divideBy2(maxQout);

    std::vector<int> multiple, remainder = dividend;
    
    int counter = 0;
    int compare_remainder_divisor_val = compareNum1andNum2(remainder, divisor);

    // Perform binary search to identify the quotient
    while (true)
    {
        multiple = multiplyFunc_ptr(currentQuotient, divisor);

        if (compareNum1andNum2(dividend, multiple) > -1)
        {
            remainder = subtract(dividend, multiple);
            minQout = currentQuotient;
        }
        else
        {
            maxQout = currentQuotient;
        }

        compare_remainder_divisor_val = compareNum1andNum2(remainder, divisor);
        if (compare_remainder_divisor_val > -1)
        {
            currentQuotient = divideBy2(add(maxQout, minQout));
        }
        else{
            remainder = subtract(dividend, multiple);
            break;
        }

        counter++;
    }

    return std::make_pair(currentQuotient, remainder);
}

// Function: numstr1/numstr2, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::string divide(std::string numstr1, std::string numstr2, std::string method)
{
    std::string numstr1_nozeros = removePrecedingZeros(numstr1);
    std::string numstr2_nozeros = removePrecedingZeros(numstr2);
    
    std::vector<int> num1 = convertNumStr2Vec(numstr1_nozeros);
    std::vector<int> num2 = convertNumStr2Vec(numstr2_nozeros);
    auto result = computeQuotientRemainder(num1, num2, method);

    return convertNumVec2Str(removePrecedingZeros(result.first));
}

// Function: numstr1%numstr2, method: "Long", "Karatsuba", "SchonhadgeStrassenRecursive", "SchonhadgeStrassenIterative"
std::string modulus(std::string numstr1, std::string numstr2, std::string method)
{
    std::string numstr1_nozeros = removePrecedingZeros(numstr1);
    std::string numstr2_nozeros = removePrecedingZeros(numstr2);
    
    std::vector<int> num1 = convertNumStr2Vec(numstr1_nozeros);
    std::vector<int> num2 = convertNumStr2Vec(numstr2_nozeros);
    auto result = computeQuotientRemainder(num1, num2, method);

    return convertNumVec2Str(result.second);
}

// Assumes no preceeding zeros and both are positive, 0-> equal, 1 -> Num1 > Num2, -1 -> Num1 < Num2
int compareNum1andNum2(std::vector<int> num1, std::vector<int> num2)
{
    // Error Check
    num1 = convertNumStr2Vec(removePrecedingZeros(convertNumVec2Str(num1)));
    num2 = convertNumStr2Vec(removePrecedingZeros(convertNumVec2Str(num2))); 

    if (num1.size() > num2.size()) // No preceeding zeros
    {
        return 1;
    } 
    else if(num1.size() == num2.size())
    {
        // if Length equal, digitwise comparison
        int ind = num1.size()-1;
        
        while (num1[ind] == num2[ind])
        {
            ind--;
        }

        if(ind < 0)
        {
            return 0;
        }
        else if (num1[ind] > num2[ind])
        {
            return 1;
        }
        else
        {
            return -1;
        }

    }
    else{
        return -1;
    }
}

