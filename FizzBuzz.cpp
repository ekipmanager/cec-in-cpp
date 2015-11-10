/*
 * FizzBuzz.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: k1
 */

// Sample code to read in test cases:
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print_fizz_buzz(int params[3]) {
    for (int i = 1; i <= params[2]; ++i) {
        if (i % params[0] == 0)
            if (i % params[1] == 0)
                cout << "FB";
            else
                cout << "F";
        else if (i % params[1] == 0)
            cout << "B";
        else
            cout << i;
        if (i < params[2])
            cout << " ";
    }

}
int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;
    string delimeter = " ";
    int test_cases[3];
    int t_num = 0;
    while (getline(stream, line)) {
        if (!line.length())
            continue;
        if (++t_num > 20)
            return 1;
        int idx = 0;
        int i = 0;
        do {
            idx = line.find(delimeter);
            if (idx == string::npos) {
                test_cases[i++] =  atoi(line.substr(0, line.length()).c_str());
                break;
            }
            test_cases[i++] = atoi(line.substr(0, idx).c_str());
            line = line.substr(idx + delimeter.length(), line.length());
        } while (line.length());
        if (test_cases[2] < 21 || test_cases[2] > 100 || test_cases[0] > 20 ||
                test_cases[0] < 1 || test_cases[1] > 20 || test_cases[1] < 1)
            return 1;
        print_fizz_buzz(test_cases);
        cout << "\n";
    }

    return 0;
}


