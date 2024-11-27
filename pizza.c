#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LENGTH 8192

struct product {
	char *name;
	float price;
	float pricePerTop;
	struct product *next;
};

struct order {
	int amount;
	int amountOfTop;
	struct product *type;
	struct order *next;
};

struct product *products;
struct order *orders;

void error(char *message, int code) {
	fprintf(stderr, "%s", message);
	exit(code);
}

void printOptions() {
	printf("\e[1;36mOptions\e[0m:\n\t\e[33m0\e[0m:\tPrint this text\n\t\e[33m1\e[0m:\tPrint menu\n\t\e[33m2\e[0m:\tPrint order\n\t\e[33m3\e[0m:\tAdd item\n\t\e[33m4\e[0m:\tCheckout\n");
}

void printMenu(struct product *curr) {
	while ( curr ) {
		printf("\e[33m┌\e[0m\t\e[1;36m%s\e[0m\n\e[33m│\e[0mPrice:\n\e[33m│\e[0m\t$%'12.2f\n\e[33m│\e[0mPrice Per Topping:\n\e[33m└\e[0m\t$%'12.2f\n", curr->name, curr->price, curr->pricePerTop);
		curr = curr->next;
	}
}

void printOrder(struct order *curr) {
	float total = 0;
	while ( curr->next ) {
		float price = (float)curr->amount * (curr->type->price + (float)curr->amountOfTop * curr->type->pricePerTop);
		total += price;
		printf("\e[33m┌\e[0m\t\e[1;36m%s\e[0m\n\e[33m│\e[0mAmount:\t\t%8d\n\e[33m│\e[0mAmount Of Toppings:\t%8d\n\e[33m└\e[0m\t$%'12.2f\n", curr->type->name, curr->amount, curr->amountOfTop, price);
		curr = curr->next;
	}
	printf("\n\e[1;36mSub Total\e[0m:\t$%'12.2f\n\e[1;36mTax\e[0m:\t\t$%'12.2f\n\e[1;36mTotal\e[0m:\t\t$%'12.2f\n", total, total * 0.06625, total * 1.06625);
}

int addItem(struct order *currOrder) {
	printf("\e[33mWhich item\e[0m? ");
	int type;
	scanf("%d", &type);
	struct product *curr = products;
	for ( int i = 0; i < type; i++ ) {
		curr = curr->next;
		if ( curr == NULL ) {
			fprintf(stderr, "Not an item\n");
			return 1;
		}
	}
	currOrder->type = curr;

	printf("\e[33mHow many\e[0m? ");
	scanf("%d", &currOrder->amount);

	printf("\e[33mHow many toppings each\e[0m? ");
	scanf("%d", &currOrder->amountOfTop);

	return 0;
}

int main() {
	FILE *fptr = fopen("products.bin", "r");

	if ( fptr == NULL )
		error("products.bin needs to exist", 1);

	char *buffer = malloc(MAX_BUFFER_LENGTH * sizeof(char));
	buffer[0] = 0;

	products = malloc(sizeof(struct product));

	struct product *curr = products;

	char ch = getc(fptr);
	if ( ch == EOF )
		error("products.bin can't be empty", 1);

	while ( 1 ) {
		int i = 0;
		while ( ch != 0 ) {
			buffer[i++] = ch;
			ch = getc(fptr);

			if ( i == MAX_BUFFER_LENGTH )
				error("string too long\n", 1);
			if ( ch == EOF )
				error("string didnt terminate\n", 1);
		}
		buffer[i] = 0;

		curr->name = malloc(sizeof(char) * (i + 1));
		memcpy(curr->name, buffer, i + 1);

		fread(&curr->price, sizeof(float), 1, fptr);
		fread(&curr->pricePerTop, sizeof(float), 1, fptr);

		if ( (ch = getc(fptr)) == EOF )
			break;

		curr->next = malloc(sizeof(struct product));
		curr = curr->next;
	}

	curr = NULL;
	free(buffer);
	fclose(fptr);

	printf("---- \e[32mWelcome to Pranav's Mom's Kitchen!\e[0m ----\n\n");
	printOptions();

	orders = malloc(sizeof(struct order));
	orders->next = NULL;
	struct order *currOrder = orders;
	int running = 1;
	while ( running ) {
		printf("$ ");
		int option = getchar();

		switch ( option - 48 ) {		// map to integers
			case 0: printOptions();		break;
			case 1: printMenu(products);	break;
			case 2: printOrder(orders);	break;
			case 3:
				if ( !addItem(currOrder) ) {
					currOrder->next = malloc(sizeof(struct order));
					currOrder = currOrder->next;
					currOrder->next = NULL;
				}
				break;
			case 4: printOrder(orders); running = 0;	break;
		}

		if ( option != '\n' ) while ( getchar() != '\n' ) {}	// special case for no input
	}
}
