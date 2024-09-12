#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double num1, num2;
    cout << "GIMME NUMBER" << endl;
    cin >> num1;
    cout << "GIMME NUMBER" << endl;
    cin >> num2;

    cout << num1 + num2 << endl << num1 - num2 << endl << num1 * num2 << endl << num1 / num2 << endl << fmod(num1, num2) << endl << round(num1*100)/100 << endl << ++num1 << endl << --num2 << endl;<M-C-F3>
}
