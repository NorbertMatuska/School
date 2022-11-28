//CV 1 uloha 3
//Norbert Matuška

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int N;
	double cislo = 0, cislo1 = 0, cislo2;

	scanf_s("%d", &N);
	cislo2 = N;
	for (int i = 0; i < N; i++) {
		scanf_s("%lf", &cislo);
		if (cislo1 < cislo) {
			cislo1 = cislo;
		}
		if (cislo2 > cislo) {
			cislo2 = cislo;
		}
		cislo = 0;
	}
	printf("Minimum: %.2lf \n", cislo2);
	printf("Maximum: %.2lf \n", cislo1);


	return 0;
}