//FIIT STU
//Norbert Matuška
//1/11/2020
//Zadanie 5, uloha cislo 3
//program prepocita zadane cislo z decimalnej sustavy do binarnej sustavy

#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>

int main() {

	int n, i;

	int bin[32];

	printf("Zadajte cislo z desiatkovej sustavy: \n");
	scanf_s("%d", &n);

	for (i = 0; n > 0; i++) {
		bin[i] = n % 2;
		n = n / 2;

	}
	printf("Vase cislo v binarnej sustave: ");

	for (i = i - 1; i >= 0; i--) {
		printf("%d", bin[i]);

	}


	return 0;
}