// DecryptTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>

using namespace std;


int strSeqToNum(string str) {
    if (str.length() == 3) {
        if (str[1] == '+')
            return int(str[0]) + int(str[2]) - 2*int('0');
        if (str[1] == '-')
            return 0;
    }

    if (str[0] == 'A')
        return 1;
    else if (str[0] == 'J')
        return 10;
    else if (str[0] == 'Q')
        return 11;
    else if (str[0] == 'K')
        return 12;
    else
        return int(str[0])- int('0');
}

string processString(string str) {
    string decrypted;
    string upper;
    string lower;
    for (int i = 0; i < str.length();) {
        if (str[i] == '\n') {
            decrypted += '\n';
            i++;
            continue;
        }

        if (i + 1 < str.length() and (str[i + 1] == '+' or str[i + 1] == '-')) {
            upper = str.substr(i, 3);
            i += 3;
        }
        else {
            upper = str[i];
            i += 1;
        }

        if (i + 1 < str.length() and (str[i + 1] == '+' or str[i + 1] == '-')) {
            lower = str.substr(i, 3);
            i += 3;
        }
        else {
            lower = str[i];
            i += 1;
        }
        decrypted += (strSeqToNum(upper) << 4) + strSeqToNum(lower);


    }
    return decrypted;
}

int main()
{
    string str;
    cin >> str;
    cout << processString(str);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file