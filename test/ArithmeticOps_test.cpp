#include <string>
#include <complex>

#include <gtest/gtest.h>
#include "ArithmeticOps.h"

// std::string add(std::string numstr1, std::string numstr2);
// std::vector<int> add(std::vector<int> num1, std::vector<int> num2)
TEST(ArithmeticOpsTest, addTest) {

    EXPECT_EQ(add(std::string("2"),std::string("3")),std::string("5"));
    EXPECT_THROW(add(std::string("-2"),std::string("3")), std::invalid_argument);
    EXPECT_THROW(add(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(add((std::vector<int>{0,0,0,123,1,1}),(std::vector<int>{1,2,4,5})), std::invalid_argument);
    EXPECT_THROW(add((std::vector<int>{0,0,-1,1}),(std::vector<int>{1,-2,5})), std::invalid_argument);
    EXPECT_EQ(add(std::string("1235"),std::string("10101")),std::string("11336"));
    EXPECT_EQ(add((std::vector<int>{0,0,0,1,1,1}),(std::vector<int>{1,2,3,4,5})),(std::vector<int>{1,2,3,5,6,1})); // 111000+54321 = 165321
    EXPECT_EQ(add(std::string("431456436841453144525654636787365754678584487841471488471847846878447484768847844378847484367483467483474684847847483467844"),std::string("8478424874841784427847884427848478824784828478414278844784452748417827184278147884798797874978246882684182683834788147837833784")),std::string("8478856331278625880992410082485266190539507062902120316272924596264705631762916732643176722462614366151666158519635995321301628"));
}

// std::string subtract(std::string numstr1, std::string numstr2)
// std::vector<int> subtract(std::vector<int> num1, std::vector<int> num2)
TEST(ArithmeticOpsTest, subtractTest) {

    EXPECT_THROW(subtract(std::string("2"),std::string("3")), std::invalid_argument);
    EXPECT_THROW(subtract(std::string("-2"),std::string("3")), std::invalid_argument);
    EXPECT_THROW(subtract(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(subtract(std::vector<int>{0,0,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_EQ(subtract(std::string("10101"),std::string("1234")),std::string("8867"));
    EXPECT_EQ(subtract((std::vector<int>{0,0,0,1,1,1}),(std::vector<int>{1,2,3,4,5})),(std::vector<int>{9,7,6,6,5})); // 111000-54321 = 56679
    EXPECT_EQ(subtract(std::string("13464154151384458144854134551433511476195867245773567847683787978798974878186571554613515776353781233672336731657336571353671375673"),std::string("257979287657336187798735073765865721687365887638768378")),std::string("13464154151384458144854134551433511476195867245773567847683787978798974878186313575325858440165982498598570865935649205466032607295"));
}

// std::string mulLong(std::string numstr1, std::string numstr2);
// std::vector<int> mulLong(std::vector<int> num1, std::vector<int> num2);
TEST(ArithmeticOpsTest, mulLongTest) {

    EXPECT_THROW(mulLong(std::string("-2"),std::string("3")), std::invalid_argument);
    EXPECT_THROW(mulLong(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(mulLong(std::vector<int>{0,0,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_EQ(mulLong(std::string("0"),std::string("1")),std::string("0"));
    EXPECT_EQ(mulLong((std::vector<int>{0,1,2,3,4,5,6}),(std::vector<int>{4,3,2,1})),(std::vector<int>{0,4,1,1,2,3,4,7,0,8}));
    EXPECT_EQ(mulLong(std::string("3644173346577777773583465733586773968743432618327814173888499887957870969988058519331361321365138334783447965878943657235167241785749378494617267194479858953617944769878915789458794589589178192781618902189023189301378910483874884268472452613254363567465374678"),std::string("7418236719865849877896875631686764484782769716917526546367656674846647865754969807899879708940684964654662565665451")),std::string("27033340533139691116588351244550270844427748367463322397604405220048759449888823436014311672863590878895892421796656179026210216206043231138768832272199776669909666916794839249604899301884583824577566374001586916778725553428499699201864238766997125372803619704425215597006453403161060014542693541675399991735148958889734679313097142821163797626628288683103817718930114849778"));

}

// std::string mulKaratsuba(std::string numstr1, std::string numstr2)
// std::vector<int> mulKaratsuba(std::vector<int> num1, std::vector<int> num2)
TEST(ArithmeticOpsTest, mulKaratsubaTest) {

    EXPECT_THROW(mulKaratsuba(std::string("-2"),std::string("3")), std::invalid_argument);
    EXPECT_THROW(mulKaratsuba(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(mulKaratsuba(std::vector<int>{0,-1,1,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_THROW(mulKaratsuba(std::vector<int>{0,45,1,65},std::vector<int>{0,1,1}), std::invalid_argument);
    EXPECT_EQ(mulKaratsuba(std::string("0"),std::string("1")),std::string("0"));
    EXPECT_EQ(mulKaratsuba((std::vector<int>{0,1,2,3,4,5,6}),(std::vector<int>{4,3,2,1})),(std::vector<int>{0,4,1,1,2,3,4,7,0,8}));
    EXPECT_EQ(mulKaratsuba(std::string("3644173346577777773583465733586773968743432618327814173888499887957870969988058519331361321365138334783447965878943657235167241785749378494617267194479858953617944769878915789458794589589178192781618902189023189301378910483874884268472452613254363567465374678"),std::string("7418236719865849877896875631686764484782769716917526546367656674846647865754969807899879708940684964654662565665451")),std::string("27033340533139691116588351244550270844427748367463322397604405220048759449888823436014311672863590878895892421796656179026210216206043231138768832272199776669909666916794839249604899301884583824577566374001586916778725553428499699201864238766997125372803619704425215597006453403161060014542693541675399991735148958889734679313097142821163797626628288683103817718930114849778"));
}


// std::string mulSchonhageStrassen(std::string numstr1, std::string numstr2, std::string method)
// std::vector<int> mulSchonhageStrassen(std::vector<int> numvec1, std::vector<int> numvec2, std::string method)
// std::vector<int> mulSchonhageStrassenIterative(std::vector<int> numvec1, std::vector<int> numvec2)
// std::vector<int> mulSchonhageStrassenRecursive(std::vector<int> numvec1, std::vector<int> numvec2)
TEST(ArithmeticOpsTest, mulSchonhageStrassenTest) {

    EXPECT_THROW(mulSchonhageStrassen(std::string("-2"),std::string("3"),std::string("Recursive")), std::invalid_argument);
    EXPECT_THROW(mulSchonhageStrassen(std::string("-2"),std::string("3"),std::string("Iterative")), std::invalid_argument);
    EXPECT_THROW(mulSchonhageStrassen(std::string("2"),std::string("3"),std::string("Random")), std::invalid_argument);
    EXPECT_THROW(mulSchonhageStrassen(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(mulSchonhageStrassen(std::vector<int>{0,-1,1,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_THROW(mulSchonhageStrassen(std::vector<int>{0,45,1,65},std::vector<int>{0,1,1}), std::invalid_argument);
    EXPECT_EQ(mulSchonhageStrassen(std::string("0"),std::string("1"),std::string("Iterative")),std::string("0"));
    EXPECT_EQ(mulSchonhageStrassen((std::vector<int>{0,1,2,3,4,5,6}),(std::vector<int>{4,3,2,1})),(std::vector<int>{0,4,1,1,2,3,4,7,0,8}));
    EXPECT_EQ(mulSchonhageStrassen(std::string("3644173346577777773583465733586773968743432618327814173888499887957870969988058519331361321365138334783447965878943657235167241785749378494617267194479858953617944769878915789458794589589178192781618902189023189301378910483874884268472452613254363567465374678"),std::string("7418236719865849877896875631686764484782769716917526546367656674846647865754969807899879708940684964654662565665451")),std::string("27033340533139691116588351244550270844427748367463322397604405220048759449888823436014311672863590878895892421796656179026210216206043231138768832272199776669909666916794839249604899301884583824577566374001586916778725553428499699201864238766997125372803619704425215597006453403161060014542693541675399991735148958889734679313097142821163797626628288683103817718930114849778"));
}


// std::string exponent(std::string numstr1, std::string numstr2, std::string method)
// std::vector<int> exponent(std::vector<int> base, std::vector<int> exponent_val, std::string method)
TEST(ArithmeticOpsTest, exponentTest) {

    EXPECT_THROW(exponent(std::string("-2"),std::string("3"),std::string("Long")), std::invalid_argument);
    EXPECT_THROW(exponent(std::string("2"),std::string("3"),std::string("Iterative")), std::invalid_argument);
    EXPECT_THROW(exponent(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(exponent(std::vector<int>{0,-1,1,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_THROW(exponent(std::vector<int>{0,45,1,65},std::vector<int>{0,1,1}), std::invalid_argument);
    EXPECT_EQ(exponent(std::string("0"),std::string("1"),std::string("SchonhadgeStrassenIterative")),std::string("0"));
    EXPECT_EQ(exponent((std::vector<int>{5,6}),(std::vector<int>{4,3})),(std::vector<int>{5,2,6,0,9,8,2,6,4,9,4,9,6,6,4,8,6,2,2,4,3,3,4,9,8,9,8,4,1,6,8,8,1,5,2,5,6,8,9,0,9,8,1,5,1,4,7,6,8,8,7,4,6,4,5,1,6,6,5,5,3,4}));
    EXPECT_EQ(exponent(std::string("123"),std::string("321")),std::string("72367033806371673149109894141163778628811792657571658906010558390395870363798401744095280686155507736404921657070284961721828960592977909542637098897697223102622628566787654091327825453991595140205701412961364188732408936197890553699715836951569999800431957769217006743321026257517932764164662319487914962533302741368207211189494615326552790667720411285474162636765168907211924134973374304496019635376665858559941735703924836467756917247995469583487467791524582153744522107597865277798136080074161485280424274076931083994487111719562249702540362855712911132265966235754355353516703339043001506118520760359577737869472018617942120590873170710805078696371738906375721785723"));
}

// int estimateQuotientDigits(std::vector<int> num1, std::vector<int> num2) 
TEST(ArithmeticOpsTest, estimateQuotientDigitsTest) {

    EXPECT_THROW(estimateQuotientDigits(std::vector<int>{0,-1,1,1},std::vector<int>{0,1,-1}), std::invalid_argument);
    EXPECT_THROW(estimateQuotientDigits(std::vector<int>{0,45,1,65},std::vector<int>{0,1,1}), std::invalid_argument);
    EXPECT_THROW(estimateQuotientDigits(std::vector<int>{0,1},std::vector<int>{0,1,2}), std::invalid_argument);
    EXPECT_EQ(estimateQuotientDigits(std::vector<int>{0,1,2},std::vector<int>{0,1}), 2);
}


// std::string divide(std::string numstr1, std::string numstr2, std::string method)
TEST(ArithmeticOpsTest, divideTest) {

    EXPECT_THROW(divide(std::string("-2"),std::string("3"),std::string("Long")), std::invalid_argument);
    EXPECT_THROW(divide(std::string("2"),std::string("3"),std::string("Iterative")), std::invalid_argument);
    EXPECT_THROW(divide(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(divide(std::string("1"),std::string("0"),std::string("SchonhadgeStrassenIterative")), std::invalid_argument);
    EXPECT_EQ(divide(std::string("1"),std::string("123456"),std::string("SchonhadgeStrassenIterative")), std::string("0"));
    EXPECT_EQ(divide(std::string("0"),std::string("1"),std::string("SchonhadgeStrassenIterative")), std::string("0"));
    EXPECT_EQ(divide(std::string("321"),std::string("123")), std::string("2"));
}


// std::string modulus(std::string numstr1, std::string numstr2, std::string method)
TEST(ArithmeticOpsTest, modulusTest) {

    EXPECT_THROW(modulus(std::string("-2"),std::string("3"),std::string("Long")), std::invalid_argument);
    EXPECT_THROW(modulus(std::string("2"),std::string("3"),std::string("Iterative")), std::invalid_argument);
    EXPECT_THROW(modulus(std::string("2"),std::string("3.14")), std::invalid_argument);
    EXPECT_THROW(modulus(std::string("1"),std::string("0"),std::string("SchonhadgeStrassenIterative")), std::invalid_argument);
    EXPECT_EQ(modulus(std::string("1"),std::string("123456"),std::string("SchonhadgeStrassenIterative")), std::string("1"));
    EXPECT_EQ(modulus(std::string("0"),std::string("1"),std::string("SchonhadgeStrassenIterative")), std::string("0"));
    EXPECT_EQ(modulus(std::string("321"),std::string("123")), std::string("75"));
}


// std::vector<int> divideBy2(std::vector<int> num)
TEST(ArithmeticOpsTest, divideBy2Test) {
    
    EXPECT_THROW(divideBy2(std::vector<int>{0,-1,1,1}), std::invalid_argument);
    EXPECT_THROW(divideBy2(std::vector<int>{0,1,13,1}), std::invalid_argument);
    EXPECT_EQ(divideBy2(std::vector<int>{0,1,1,1}), (std::vector<int>{5,5,5,0}));
}


// int compareNum1andNum2(std::vector<int> num1, std::vector<int> num2)
TEST(ArithmeticOpsTest, compareNum1andNum2Test) {
    
    EXPECT_THROW(compareNum1andNum2(std::vector<int>{0,-1,1,1}, std::vector<int>{0,1,1,1}), std::invalid_argument);
    EXPECT_THROW(compareNum1andNum2(std::vector<int>{0,1,1,1}, std::vector<int>{0,1,13,1}), std::invalid_argument);
    EXPECT_EQ(compareNum1andNum2(std::vector<int>{0,1,1,1}, std::vector<int>{0,1,1,1}), 0);
    EXPECT_EQ(compareNum1andNum2(std::vector<int>{0,1,1,1}, std::vector<int>{0,0,0,1}), 1);
    EXPECT_EQ(compareNum1andNum2(std::vector<int>{0,0,0,1}, std::vector<int>{0,1,1,1}), -1);
}
