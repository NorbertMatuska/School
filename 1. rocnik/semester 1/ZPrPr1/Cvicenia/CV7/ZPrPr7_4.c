#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void prehod(int*, int*);

int main() {

	int a, b;

	printf("Zadaj hodnotu premennej a:\n");
	scanf("%d", &a);

	printf("Zadaj hodnotu premennej b:\n");
	scanf("%d", &b);


	prehod(&a, &b);

	printf("Hodnota a: %d, hodnota b: %d", a, b);


	return 0;
}

void prehod(int* pa, int* pb) {

	int p; //Docasna pomocna premenna na prehodenie znakov

	p = *pa;
	*pa = *pb;
	*pb = p;

}