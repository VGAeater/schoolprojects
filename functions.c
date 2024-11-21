#include <stdio.h>

void countdown() {
	for (int i = 10; i > 0; i--)
		printf("%d\n", i);
	printf("Lift off!\n");
}

void customGreet(char* name, int times) {
	for (int i = 0; i < times; i++)
		printf("Hello, %s!\n", name);
}

int getFavoriteNumber() { return 12; }

int calculateAverage(int a, int b, int c) { return (a + b + c) / 3; }

int main() {
	countdown();
	customGreet("Stratton", getFavoriteNumber());
	int favNumber = getFavoriteNumber();
	int a, b, c;
	printf("enter 3 nums: ");
	scanf("%d %d %d", &a, &b, &c);
	printf("avg is: %d\n", calculateAverage(a, b, c));
}
