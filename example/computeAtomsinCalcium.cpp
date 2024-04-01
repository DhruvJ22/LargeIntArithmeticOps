#include <iostream>
#include <string>
#include <complex>
#include <algorithm>

#include "ArithmeticOps.h"

int main(){
    
    std::string MolarMass, AvogadroNum, GivenMass, NumMoles, NumAtoms;

    // Molar Mass of Calcium = 40800 mg
    MolarMass = "40800";
    // Avogadro's number = 6.022 x 10^23
    std::string zeros(23, '0');
    AvogadroNum = "6022" + zeros;
    std::cout << "AvogadroNum: " << AvogadroNum << std::endl;
    
    std::cout << "Enter the weight of given Calcium sample (g): ";
    std::cin >> GivenMass;
    // Given Mass, change units g -> mg
    GivenMass = mulKaratsuba(GivenMass, "1000"); 

    // Compute number of moles of Ca
    NumMoles = divide(GivenMass, MolarMass);
    // Total number of atoms in the sample
    NumAtoms = mulSchonhageStrassen(NumMoles, AvogadroNum);

    std::cout << "Number of atoms in given Calcium sample: " << NumAtoms << std::endl;

    return 0;

}