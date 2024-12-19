//FIIT STU
//Norbert Matuška
//1/11/2020
//Zadanie 5, uloha cislo 5
//bohuzial som tuto ulohu nevedel

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 12


int main() {
	
	int x[N], i;

	x[0] = 1;

	//vypise mesiace
	for (i = 0; i < N; i++)
		x[i] = i + 1;
	
	for (i = 0; i < N; i++)
		printf("x[%d]: %d\n", i, x[i]);
		

	return 0;
}