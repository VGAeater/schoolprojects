// Stratton Jelley
// 12/16/2024
// Time Date

#include <stdio.h>
#include <time.h>

int main() {
	// Task 1: Display local time
	time_t t;
	struct tm *tm_info;
	time(&t);
	tm_info = localtime(&t);
	printf("Local time: %s", asctime(tm_info));

	// Task 2: Calculate time zone offset
	int offset;
	printf("\nEnter UTC offset (in hours): ");
	scanf("%d", &offset);
	tm_info = gmtime(&t);
	tm_info->tm_hour += offset;
	mktime(tm_info);
	printf("Current time in UTC offset %d: %s", offset, asctime(tm_info));

	// Task 3: Calculate time to answer question
	char input;
	printf("\nPress Enter when you are ready to start...\n");
	getchar();  // Wait for user to press Enter
	time(&t);

	printf("Now, answer this question: What is 2 + 2?\n");
	getchar();  // Wait for user to press Enter after answering
	double time_taken = time() - t;
	printf("Time taken to answer: %.2f seconds\n", time_taken);

	return 0;
}
