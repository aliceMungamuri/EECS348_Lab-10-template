#include <iostream>
#include <fstream>
#include <string>
#include "calculator.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Please provide the input file." << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Input file cannot be opened." << endl;
        return 1;
    }

    string line;
    string base = "-123.456";

    while (getline(inFile, line)) {
        if (!validDouble(line)) {
            cout << line << " is invalid." << endl;
        } else {
            string result = addDoubles(line, base);
            cout << "Result of adding " << line << " with -123.456 = " << result << endl;
        }
    }

    inFile.close();
    return 0;
}
