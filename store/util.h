#ifndef UTIL_H_
#define UTIL_H_

int clamp(int x, int min, int max);
float fclamp(float x, float min, float max);

int min(int a, int b);

int max(int a, int b);

void appendChar(char *str, char ch);

void insertChar(char *str, char ch, int i);

void popChar(char *str);

void rmChar(char *str, int i);

#endif
