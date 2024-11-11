#include <stdio.h>
#include <stdlib.h>

struct entry {
	char *string;
	size_t size;
	struct entry *next;
};

int main() {
	struct entry first;
	struct entry *curr = &first;
	while (1) {
		printf("write something:\n");
		getline(&curr->string, &curr->size, stdin);
		printf("go again? ");
		if (getc(stdin) != 'y')
			break;
		while (getc(stdin) != '\n') {}
		struct entry *next = malloc(sizeof(struct entry*));
		curr->next = next;
		curr = next;
	}

	printf("\n\n");
	curr = &first;
	while (1) {
		printf("%s", curr->string);
		curr = curr->next;
		if (curr == NULL)
			break;
	}
}
