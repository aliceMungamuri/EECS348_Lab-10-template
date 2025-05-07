#include "calculator.hpp"
#include <string>
double parse_number(const std::string &expression){
    int i = 0;
    bool isNegative;
    int len = expression.length();
    if(expression[i]=='+'||expression[i]=='-'){
        if(expression[i]=='-'){
            isNegative = true;
        }
        i++;
    }
    double integerPart = 0.0;
    while (i < len && expression[i] != '.') {
        integerPart = integerPart * 10 + (expression[i] - '0');
        i++;
    }
    double fractionalPart = 0.0;
    if(i < len && expression[i]=='.'){
        i++;
        double divisor = 10.0;
        while(i< len){
            fractionalPart += (expression[i]-'0')/divisor;
            divisor *= 10.0;
            i++;
        }

    }
    if(isNegative){
        return -(integerPart+fractionalPart);
    }
    return integerPart+fractionalPart;
}
