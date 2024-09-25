/*
Name: Stratton
Program: calculator
date: 9/25
Extra: calc is in one line
*/

#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    // set
    double num1, num2;
    cout << "GIMME NUMBER" << endl;
    cin >> num1;
    cout << "GIMME NUMBER" << endl;
    cin >> num2;

    // calculate
    cout << num1 + num2 << endl << num1 - num2 << endl << num1 * num2 << endl << num1 / num2 << endl << fmod(num1, num2) << endl << round(num1*100)/100 << endl << ++num1 << endl << --num2 << endl;<M-C-F3>
}
