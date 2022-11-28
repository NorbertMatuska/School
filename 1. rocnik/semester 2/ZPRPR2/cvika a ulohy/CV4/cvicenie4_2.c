#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {

	int cislo1 = 0;
	int cislo2 = 0;
	int* max = 0;

	printf("Zadajte dve cele cisla\n");
	scanf("%d %d", &cislo1, &cislo2);

	printf("cisla:%d %d\nadresy: %u %u\n", cislo1, cislo2, &cislo1, &cislo2);

	max = maximum(&cislo1, &cislo2);
	printf("vacsie cislo:%d adresa:%u\n",*max, max);

	return 0;
}

int maximum(int *cislo1,int *cislo2) {

	int temp = 0;
	if (*cislo1 > *cislo2) {
		return cislo1;
	}
	else {
		return cislo2;
	}


}