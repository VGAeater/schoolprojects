// Stratton Jelley
// 10/7/2024
// Extra: beutifule formating and short and scanf so its better

#include <stdio.h>

int main() {
	int hello;
	printf("HOW ARE YOU FEELING:\n1: HAPPY\n2: SAD\n3: MAD\n4: TIRED\n5: BORED\n");
	scanf("%d", &hello);
	switch(hello) {
		case 1:  printf("thats nice :)\n");      break;
		case 2:  printf("imagine\n");            break;
		case 3:  printf("hahahahaa\n");          break;
		case 4:  printf("get some sleep lol\n"); break;
		case 5:  printf("same :/\n");            break;
		default: printf("fkjsHEIGURKSJFHGsyuh\n");
	}
}
