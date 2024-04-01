#include <iostream>
#include <string>
#include <unordered_map>

#include "ArithmeticOps.h"
#include "TypeManipulation.h"

int main(){
    
    std::string base, exponent_val, result; 
    char MethodKey;
    std::unordered_map<int, std::string> MethodMap;
    MethodMap[0] = "Long";
    MethodMap[1] = "Karatsuba";
    MethodMap[2] = "SchonhadgeStrassenRecursive";
    MethodMap[3] = "SchonhadgeStrassenIterative";

    std::cout << "Enter the base: ";
    std::cin >> base;
    std::cout << "Enter the exponent_val: ";
    std::cin >> exponent_val;

    do
    {
        std::cout << "Multiplication method (0 - Long, 1 - Karatsuba, 2 - SchonhadgeStrassenRecursive, 3 - SchonhadgeStrassenIterative)\nEnter the option number (0,1,2,3): ";
        std::cin >> MethodKey;
    } while (convertDigitChar2Int(MethodKey) > 3);
    
    try{
        result = exponent(base, exponent_val, MethodMap[convertDigitChar2Int(MethodKey)]);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
    }

    return 0;

}