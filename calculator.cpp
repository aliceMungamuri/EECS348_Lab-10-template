#include "calculator.hpp"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool validDouble(const string& str) {
    if (str.empty()) return false;

    int i = 0;
    if (str[0] == '+' || str[0] == '-') i++;

    bool digitsBeforeDot = false;
    while (i < str.length() && str[i] != '.') {
        if (!isdigit(str[i])) return false;
        digitsBeforeDot = true;
        i++;
    }

    bool hasDot = false;
    bool digitsAfterDot = false;
    if (i < str.length() && str[i] == '.') {
        hasDot = true;
        i++;
        while (i < str.length()) {
            if (!isdigit(str[i])) return false;
            digitsAfterDot = true;
            i++;
        }
    }

    if (!digitsBeforeDot && (!hasDot || !digitsAfterDot)) return false;
    if (hasDot && !digitsAfterDot) return false;

    return true;
}

void normalize(string &int1, string &frac1, string &int2, string &frac2) {
    while (int1.length() < int2.length()) int1 = '0' + int1;
    while (int2.length() < int1.length()) int2 = '0' + int2;
    while (frac1.length() < frac2.length()) frac1 += '0';
    while (frac2.length() < frac1.length()) frac2 += '0';
}

string addStrings(const string &a, const string &b) {
    string result = "";
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result += (sum % 10 + '0');
        carry = sum / 10;
    }
    if (carry) result += (carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

string subtractStrings(const string &a, const string &b) {
    string result = "";
    int borrow = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int diff = (a[i] - '0') - (b[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;
        result += (diff + '0');
    }
    reverse(result.begin(), result.end());
    return result;
}

bool isSmaller(const string &a, const string &b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}

string stripZeros(const string &s, bool fromFront) {
    if (s.empty()) return "0";
    if (fromFront) {
        size_t i = 0;
        while (i < s.length() - 1 && s[i] == '0') i++;
        return s.substr(i);
    } else {
        int i = s.size() - 1;
        while (i >= 0 && s[i] == '0') i--;
        return i >= 0 ? s.substr(0, i + 1) : "0";
    }
}

string addDoubles(const string& a_raw, const string& b_raw) {
    string a = a_raw, b = b_raw;
    bool negA = false, negB = false;
    if (a[0] == '-') { negA = true; a = a.substr(1); }
    if (a[0] == '+') a = a.substr(1);
    if (b[0] == '-') { negB = true; b = b.substr(1); }
    if (b[0] == '+') b = b.substr(1);

    size_t dotA = a.find('.'), dotB = b.find('.');
    string intA = dotA != string::npos ? a.substr(0, dotA) : a;
    string fracA = dotA != string::npos ? a.substr(dotA + 1) : "";
    string intB = dotB != string::npos ? b.substr(0, dotB) : b;
    string fracB = dotB != string::npos ? b.substr(dotB + 1) : "";

    normalize(intA, fracA, intB, fracB);

    string resultFrac, resultInt;

    if (negA == negB) {
        resultFrac = addStrings(fracA, fracB);
        int carry = 0;
        if (resultFrac.length() > fracA.length()) {
            carry = 1;
            resultFrac = resultFrac.substr(1);
        }
        resultInt = addStrings(intA, intB);
        if (carry) {
            int i = resultInt.length() - 1;
            while (i >= 0 && resultInt[i] == '9') {
                resultInt[i] = '0';
                i--;
            }
            if (i >= 0) resultInt[i]++;
            else resultInt = "1" + resultInt;
        }
        string final = stripZeros(resultInt, true);
        if (!fracA.empty()) final += "." + stripZeros(resultFrac, false);
        if (negA) final = "-" + final;
        return final;
    } else {
        bool aIsBigger = isSmaller(intA + fracA, intB + fracB) == false;
        string biggerInt = aIsBigger ? intA : intB;
        string biggerFrac = aIsBigger ? fracA : fracB;
        string smallerInt = aIsBigger ? intB : intA;
        string smallerFrac = aIsBigger ? fracB : fracA;
        resultFrac = subtractStrings(biggerFrac, smallerFrac);
        int borrow = 0;
        for (int i = resultFrac.length() - 1; i >= 0; i--) {
            if (resultFrac[i] < '0') {
                resultFrac[i] += 10;
                borrow = 1;
            }
        }
        resultInt = subtractStrings(biggerInt, smallerInt);
        if (borrow) {
            int i = resultInt.length() - 1;
            while (i >= 0 && resultInt[i] == '0') {
                resultInt[i] = '9';
                i--;
            }
            if (i >= 0) resultInt[i]--;
        }

        string final = stripZeros(resultInt, true);
        if (!fracA.empty()) final += "." + stripZeros(resultFrac, false);
        if ((negA && aIsBigger) || (negB && !aIsBigger)) final = "-" + final;
        return final;
    }
}
