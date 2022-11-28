//FIIT STU
//Norbert Matuška
//1/11/2020
//Zadanie 5, uloha cislo 2
//program vypocita priemernu spotrebu auta na 100km pomocou zadanych hodnot od uzivatela

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	float km, l, priemer;

	printf("Zadajte prejdenu vzdialenost automobilu (v km): \n");
	scanf("%f", &km);
	printf("Zadajte spotrebovane palivo: \n");
	scanf("%f", &l);

	priemer = (l / km);
	priemer *= 100;

	printf("spotreba je: %f l/100km", priemer);


	return 0;
}