/*
 * Name: Stratton
 * Program: calculator
 * date: 9/25
 * Extra: calc is in one line
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	// Exercise 1:
	char quotes[7][25];	// 24 + null
	char *DoW[7] = { "Monday", "Teusday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

	for (int i = 0; i < 7; i++) {
		printf("%s\nEnter Quote: \n", DoW[i]);
		fgets(quotes[i], 25, stdin);
	}

	printf("\n");
	for (int i = 0; i < 7; i++)
		printf("%s\n", quotes[i]);

	// Exercise 2:
	int energy = 5, supplies = 0, day = 0;

	while (energy > 0 && supplies < 10) {
		int choice;
		day++;

		printf("\nDay %d:\n1. Search for supplies (costs 1 energy, adds 1 supply)\n2. Rest(restores 2 energy, but doesn’t add supplies)\n", day);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				energy--;
				supplies++;
				printf("Energy: %d\nSupplies: %d\n", energy, supplies);
				break;
			case 2:
				energy += 2;
				break;
		}

		if (supplies >= 10)
			printf("\nCongratulations\n");
		else if (energy <= 0)
			printf("\nYou lost!\n");
	}

	// Exercise 3
	srand(time(NULL));
	int randNumber = rand();

	printf("%d", &randNumber);

	int guess;
	int tryAgain;

	do {
		printf("Enter the three digit passcode: \n");
		scanf("%d", guess);

		if (guess == randNumber) {
			printf("You unlocked the box!\n");
			break;
		}
		printf("Do you want to try again? (Y/N)\n");
		tryAgain = getc(stdin);
	} while (tryAgain != 'N' && tryAgain != 'n');
}
