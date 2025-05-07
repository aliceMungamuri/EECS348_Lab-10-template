#include <iostream>
#include <fstream>
#include <string>
#include "calculator.hpp"
using namespace std;
bool validDouble(const string& str){
    int len = str.length();
    if(len == 0){
        return false;
    }
    int i = 0;

    if(str[0]=='+'||str[0]=='-') i++;
    bool digitsBeforeDot = false;
    while(i < len && str[i] != '.'){
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
        digitsBeforeDot = true;
        i++;
    }
    bool hasDot = false;
    bool digitsAfterDot = false;
    if(str[i]=='.'){
        i++;
        hasDot = true;
        while(i <len){
            if (!(str[i] >= '0' && str[i] <= '9')) {
                return false;
            }
            digitsAfterDot = true;
            i++;
        }
    }
    if(digitsAfterDot && !digitsBeforeDot) return false;
    if(digitsBeforeDot && hasDot && !digitsAfterDot) return false;
    if(!digitsBeforeDot && hasDot) return false;
    return true;
}
int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        cout << "Please provide the input file." << endl;
        exit(1);
    }
    
    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.is_open())
    {
        string str;
        while(std::getline(inFile, str))
        {
            if(!validDouble(str)){
                cout<< str << " is invalid.\n";
                continue;
            }
            double result = -123.456 + parse_number(str);
            cout<< "Result of adding " << str << " with -123.456 = " << result<<endl;
        }
    }
    else
    {
        cout << "Input file cannot be opened" << endl;
        exit(1);
    }
    inFile.close();
    return 0;

}
