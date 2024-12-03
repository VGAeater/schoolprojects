#include "util.h"
#include <string.h>

int clamp(int x, int min, int max) { return x > max ? max : (x < min ? min : x); }
float fclamp(float x, float min, float max) { return x > max ? max : (x < min ? min : x); }

int min(int a, int b) { return a < b ? a : b; }

int max(int a, int b) {	return a > b ? a : b; }

void appendChar(char *str, char ch) {
	int len = strlen(str);
	str[len] = ch;
	str[len + 1] = '\0';
}

void insertChar(char *str, char ch, int i) {
	int len = strlen(str);
	memmove(&str[i + 1], &str[i], len - i);
	str[i] = ch;
}

void popChar(char *str) {
	int len = strlen(str);
	str[len-1] = '\0';
}

void rmChar(char *str, int i) {
	memmove(&str[i], &str[i + 1], strlen(str) - i);
}

