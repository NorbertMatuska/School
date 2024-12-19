#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {

	FILE* cisla, * vstup;
	char str[100];
	int counter, countL = 0;
	
	vstup = fopen("vstup.txt", "r");
	if (vstup == NULL) {
		printf("file couldnt be opened correctly or it doesnt exist\n");
		return 0;
	}

	cisla = fopen("cisla.txt", "a");
	if (cisla == NULL) {
		printf("file couldnt be opened correctly or it doesnt exist\n");
		return 0;
	}

	while (vstup != EOF) {
		if (fgets(str, 100, vstup) != '\0') {
			puts(str);
			fputs(str, cisla);

			for (counter = 0; str[counter] != NULL; counter++) {

				if (str[counter] >= 'a' && str[counter] <= 'z')
					countL++;
			}
			printf("%d\n", countL);
		}
	}
	return 0;
}