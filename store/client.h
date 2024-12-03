#include <stdbool.h>

#ifndef CLIENT_H_
#define CLIENT_H_

struct product {
	int *amountincart;
	int amountofoptions;
	int id;
	float *price;
	float rating;
	bool onsale;
	char *name;
	char *description;
	char *shortdesc;
	char **options;
};

#endif
