#include <iostream>
#include <string>
#include <complex>
#include <unordered_map>

#include "TypeManipulation.h"
#include "FFTHelperFuncs.h"
#include "ArithmeticOps.h"

int get_multiplication_method_opt()
{
    char MethodKey;
    do {
        std::cout << "Multiplication method (0 - Long, 1 - Karatsuba, 2 - SchonhadgeStrassenRecursive, 3 - SchonhadgeStrassenIterative)\nEnter the option number (0,1,2,3): ";
        std::cin >> MethodKey;
    } while (convertDigitChar2Int(MethodKey) > 3);

    return convertDigitChar2Int(MethodKey);
}

int main(){
    
    char operation;
    std::string operand1, operand2, result;
    int MethodKey;
    std::vector<int> temp_result;
    std::vector<int> (*multiplyFunc)(std::vector<int>, std::vector<int>) = selectMultiplyFunction("Long");
    std::unordered_map<int, std::string> MethodMap;
    MethodMap[0] = "Long";
    MethodMap[1] = "Karatsuba";
    MethodMap[2] = "SchonhadgeStrassenRecursive";
    MethodMap[3] = "SchonhadgeStrassenIterative";

    while (true) {
        // Display menu
        std::cout << "Large Integer Arithmentic Operations Menu:" << std::endl;
        std::cout << "1. Addition (+)" << std::endl;
        std::cout << "2. Subtraction (-)" << std::endl;
        std::cout << "3. Multiplication (*)" << std::endl;
        std::cout << "4. Division (/)" << std::endl;
        std::cout << "5. Modulus (%)" << std::endl;
        std::cout << "6. Exponentiation (^)" << std::endl;
        std::cout << "7. Quit" << std::endl;
        std::cout << "Enter your choice (1,2,3,4,5,6,7): ";

        // Get user's choice
        std::cin >> operation;

        // Check if user wants to quit
        if (operation == '7') {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        do
        { 
            try{
                // Get operands from the user
                std::cout << "Enter operand 1: ";
                std::cin >> operand1;
                std::cout << "Enter operand 2: ";
                std::cin >> operand2;
                operand1 =  removePrecedingZeros(convertNumVec2Str(convertNumStr2Vec(operand1)));
                operand2 =  removePrecedingZeros(convertNumVec2Str(convertNumStr2Vec(operand2)));
                break;
            } catch (const std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
                std::cout << std::endl <<"Reenter operands." << std::endl;
            }
        } while (true);

        // Perform the selected operation
        switch(operation) {
            case '1':
                result = add(operand1, operand2);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            case '2':
                result = subtract(operand1, operand2);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            case '3':
                MethodKey = get_multiplication_method_opt();
                multiplyFunc = selectMultiplyFunction(MethodMap[MethodKey]);

                temp_result = multiplyFunc(convertNumStr2Vec(operand1), convertNumStr2Vec(operand2));
                result = convertNumVec2Str(temp_result);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            case '4':
                MethodKey = get_multiplication_method_opt();

                result = divide(operand1, operand2, MethodMap[MethodKey]);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            case '5':
                MethodKey = get_multiplication_method_opt();

                result = modulus(operand1, operand2, MethodMap[MethodKey]);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            case '6':
                MethodKey = get_multiplication_method_opt();

                result = exponent(operand1, operand2, MethodMap[MethodKey]);
                std::cout << "Result: " << result << std::endl << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please enter a valid option." << std::endl << std::endl;
        }
    }

    return 0;
}



//     std::string input_num1, input_num2;

//     std::cout << "Enter a number (0-99999): ";
//     std::cin >> input_num1;
//     std::cout << "Enter a number (0- < num1): ";
//     std::cin >> input_num2;

// //    std::string exponent_val = exponent(input_num1, input_num2);
// //    std::cout << "exponent: " << exponent_val << std::endl;

//     // std::string ans = subtract(input_num1, input_num2);
//     // std::cout << "Sub: " << ans << std::endl;

//     // std::string quotient = divide(input_num1, input_num2, "SchonhadgeStrassen");
//     // std::string remainder = modulus(input_num1, input_num2);

//     // std::cout << "quotient: " << quotient << std::endl;
//     // std::cout << "remainder: " << remainder << std::endl;

//     // // std::cout << "compare_remainder_divisor: " << compareNum1andNum2(convertNumStr2Vec(input_num2), convertNumStr2Vec(remainder)) << std::endl;

//     // std::string ans_mul = mulLong(input_num2, quotient);
//     // std::cout << "Mul: " << ans_mul << std::endl;

//     // // std::string ans = subtract(input_num1, ans_mul);
//     // // std::cout << "Remainder through sub: " << ans << std::endl;

//     std::string ans = mulLong(input_num1, input_num2);
//     std::cout << "Mul: " << ans << std::endl;

//     std::string mulFFT = mulSchonhageStrassen(input_num1, input_num2, "Iterative");
//     std::string mulKar = mulKaratsuba(input_num1, input_num2);

//     std::cout << "FFT: " << mulFFT << std::endl;
//     std::cout << "Kar: " << mulKar << std::endl;
//     std::cout << "Dif: " << subtract(mulKar, mulFFT) << std::endl;

// //    std::string exponent = numObj.computeExponentBySquaring(input_num1, input_num2, "karatsuba");

// //    std::cout << "exponent: " << exponent << std::endl;

//     // // Exponentiation by squaring
//     // auto start1 = std::chrono::high_resolution_clock::now();
//     // std::cout << "Result: " << input_num1 << "*" << input_num2 << " is " 
//     // << std::endl << numObj.computeExponentBySquaring(input_num1, input_num2) << std::endl;
//     // auto end1 = std::chrono::high_resolution_clock::now();
//     // std::chrono::duration<double> duration1 = end1 - start1;
//     // std::cout << "Runtime of long mul: " << duration1.count() << " seconds" << std::endl;

//     // // GMP
//     // auto start2 = std::chrono::high_resolution_clock::now();
//     // mpz_t base, result;
//     // char baseStr[1000];
//     // unsigned long int exponent;

//     // // Initialize base and result
//     // mpz_init(base);
//     // mpz_init(result);

//     // // Get base from the user
//     // std::cout << "Enter the base: ";
//     // std::cin.getline(baseStr, 1000);
//     // mpz_set_str(base, baseStr, 10);

//     // // Get exponent from the user
//     // std::cout << "Enter the exponent: ";
//     // std::cin >> exponent;

//     // // Compute base raised to the power of exponent
//     // mpz_pow_ui(result, base, exponent);
    
//     // gmp_printf("Result: %Zd\n", result);
//     // mpz_clear(base);
//     // mpz_clear(result);
//     // auto end2 = std::chrono::high_resolution_clock::now();
//     // std::chrono::duration<double> duration2 = end2 - start2;
//     // std::cout << "Runtime of GMP: " << duration2.count() << " seconds" << std::endl;

//     // auto start2 = std::chrono::high_resolution_clock::now();
//     // std::cout << "Result: " << input_num1 << "*" << input_num2 << " is " 
//     // << std::endl << numObj.computeExponentBySquaring(input_num1, input_num2, "karatsuba") << std::endl;
//     // auto end2 = std::chrono::high_resolution_clock::now();
//     // std::chrono::duration<double> duration2 = end2 - start2;
//     // std::cout << "Runtime of karatsuba: " << duration2.count() << " seconds" << std::endl;

//     // Compute and display, num ^ num_reverse
//     // std::cout << "Result: " << input_num1 << "*" << input_num2 << " is " 
//     // << std::endl << numObj.computeKaratsubaMul(input_num1, input_num2) << std::endl;

//     return 0;
// }


// // while(true) // Repeat input prompt if input value is invalid
// //     {
// //         std::cout << "Enter a number (0-99999): ";
// //         std::cin >> input_num;

// //         try
// //         {
// //             ReverseDigitExponentialNum numObj = ReverseDigitExponentialNum::create(input_num); // Call Factory function

// //             // Compute and display, num ^ num_reverse
// //             std::cout << "Result: " << numObj.getNum() << "^" << numObj.getNumReverse() << " is " 
// //             << std::endl << numObj.computeReversedDigitExponent() << std::endl;

// //             break;
// //         } 
// //         catch (const std::invalid_argument& statement) 
// //         {
// //             std::cout << "Error! : " << statement.what() << std::endl;
// //         }
// //     }
