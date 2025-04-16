#include "calculator.hpp"
#include <cstdlib>  // for std::stod

double parse_number(const std::string &expression) {
    return std::stod(expression);
}
