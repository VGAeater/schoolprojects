// stratton jelley
// haunted house
// extra: based on file			// use https://charactercounter.com/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	char *message;
	int option1;
	int option2;
	bool end;
};

struct node **nodes;

int main() {
	FILE *fptr = fopen("nodes.dat", "r");

	if (fptr == NULL) {
		printf("The nodes.dat file needs to exist");
		return 1;
	}

	char *buffer = malloc(5 * sizeof(char));
	buffer[4] = 0;

	fread(buffer, sizeof(char), 4, fptr);
	fgetc(fptr);				// eat return carrige cuz i aint editing no ugly aah file
	int amountOfNodes = atoi(buffer);
	//printf("Amount of nodes:\t%d\n", amountOfNodes);

	free(buffer);

	nodes = malloc(amountOfNodes * sizeof(struct node *));

	for (int index = 0; index < amountOfNodes; index++) {
		nodes[index] = malloc(sizeof(struct node));

		nodes[index]->end = fgetc(fptr) == '1';

		buffer = malloc(5 * sizeof(char));
		buffer[4] = 0;

		fread(buffer, sizeof(char), 4, fptr);
		nodes[index]->option1 = atoi(buffer);

		fread(buffer, sizeof(char), 4, fptr);
		nodes[index]->option2 = atoi(buffer);

		fread(buffer, sizeof(char), 4, fptr);
		int messageLength = atoi(buffer);

		free(buffer);
		buffer = malloc((messageLength+1) * sizeof(char));
		buffer[messageLength] = 0;

		fread(buffer, sizeof(char), messageLength, fptr);
		nodes[index]->message = buffer;		// transfer ownership
		buffer = NULL;				// dont free because its the nodes now

		fgetc(fptr);				// eat return carrige cuz i aint editing no ugly aah file
		//printf("\t%d) %d %d %d %s\n", index, nodes[index]->end, nodes[index]->option1, nodes[index]->option2, nodes[index]->message);
	}

	int curNode = 0;
	int c;

	while (true) {
		printf("%s\n", nodes[curNode]->message);
		if (nodes[curNode]->end) { return 0; }
		c = getchar();
		curNode = (c == '1') ? nodes[curNode]->option1 : nodes[curNode]->option2;
		while (getchar() != 10) { }
	}
}
