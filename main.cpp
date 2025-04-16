#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "calculator.hpp"

// Helper to trim whitespace
std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Check if a string is a valid double
bool is_valid_double(const std::string &s) {
    size_t i = 0;
    int len = s.length();
    bool has_digits = false;
    bool has_decimal = false;

    if (len == 0) return false;

    if (s[i] == '+' || s[i] == '-') i++;
    if (i == len) return false;

    while (i < len) {
        if (isdigit(s[i])) {
            has_digits = true;
        } else if (s[i] == '.') {
            if (has_decimal) return false;
            has_decimal = true;
            if (i + 1 >= len || !isdigit(s[i + 1])) return false;
        } else {
            return false;
        }
        i++;
    }

    return has_digits;
}

// Add valid double strings using parse_number
std::string add_string_doubles(const std::string &s1, const std::string &s2) {
    double result = parse_number(s1) + parse_number(s2);
    return std::to_string(result);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string num = trim(line);
        if (is_valid_double(num)) {
            std::string sum = add_string_doubles(num, "-123.456");
            std::cout << "Valid: " << num << " + (-123.456) = " << sum << "\n";
        } else {
            std::cout << "Invalid number: " << num << "\n";
        }
    }

    file.close();
    return 0;
}
