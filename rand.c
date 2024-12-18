// Stratton
// 12/18/2024
// Random / round

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main() {
	double x;
	cout << "Enter a number: " << endl;
	cin >> x;
	// round number
	cout << round(x * 100.0) / 100.0 << endl;

	srand((int)time(0));
	// rand number out of 10 
	cout << (rand() % 10) + 1 << endl;
}
