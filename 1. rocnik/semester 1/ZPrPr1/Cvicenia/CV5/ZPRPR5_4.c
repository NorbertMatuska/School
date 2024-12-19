//FIIT STU
//Norbert Matuška
//1/11/2020
//Zadanie 5, uloha cislo 4
//program pracuje ako bankovy automat, vypise moznosti prace s automatom a nasledne pracuje s hodnotami od uzivatela

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	
	int x;
	int choice, p;
	int bu = 1000;
	int pokracovat = 1;

	while (pokracovat) {

		printf("Volba 1: Vlozenie sumy penazi na bankovy ucet\n");
		printf("Volba 2: Vyber sumy penazi z bankoveho uctu\n");
		printf("Volba 3: Zistenie stavu na bankovom ucte \n");
		printf("Volba 4: Koniec cinnosti automatu \n");

		scanf_s("%d", &x);


		switch (x) {
		case 1:
			printf("Kolko chcete vlozit?\n");
			scanf_s("%d", &p);

			bu += p;

			printf("Vase peniaze boli vlozene\n \n");
			break;

		case 2:
			printf("Kolko chcete vybrat?\n");
			scanf_s("%d", &p);

			bu -= p;

			printf("Vase peniaze boli vybrane\n \n");
			break;

		case 3:
			printf("Na vasom ucte sa nachadza %d eur\n \n", bu);
			break;

		case 4:
			printf("Naozaj chcete ukoncit program?\n1 ano 2 nie\n");
			scanf_s("%d", &choice);
			if (choice == 1) {
				pokracovat = 0;
			}
		default:
			break;
		}

	}
	return 0;
}