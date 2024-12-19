//FIIT STU
//Norbert Matuška
//1/11/2020
//Zadanie 5, uloha cislo 1
//Program vypocita koeficient zvysenia vykonnosti sekvencneho programu po paralelizacii pomocou zadanych hodnot od uzivatela

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int seq, par, s;

	printf("Zadajte cas spracovania sekvencneho programu: \n");
	scanf("%d", &seq);
	printf("Zadajte cas spracovania paralelneho programu: \n");
	scanf("%d", &par);

	s = seq / par;

	printf("koeficient zvysenia vykonnosti sekvencneho programu po paralelizacii je %d \n", s);


	return 0;
}