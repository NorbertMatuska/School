#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	FILE* novy, * znak;
	znak = fopen("znak.txt", "r");
	
	if (znak == NULL) {
		printf("file couldnt be opened correctly or it doesnt exist\n");
		return 0;
	}

	char ch;
	printf("Zadajte znak:\n");
	scanf("%c", &ch);

	if (ch == 's') {
		novy = fopen("novy.txt", "w");

		if (novy == NULL) {
			printf("file couldnt be opened correctly or it doesnt exist\n");
			return 0;
		}
		while ((ch = fgetc(znak)) != EOF)
			fputc(ch, novy);
		
	}
	else
		while ((ch = fgetc(znak)) != EOF)
			printf("%c", ch);
	return 0;
}