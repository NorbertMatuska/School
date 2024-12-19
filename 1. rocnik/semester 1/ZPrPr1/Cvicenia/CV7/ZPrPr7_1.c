#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void sucet(int *ax, int *by, int *cs) {

	*cs = *ax + *by;
}

int main() {
	int x, y, s;
	int* px, * py, * ps;

	px = &x;
	py = &y;
	ps = &s;

	printf("Zadajte dve cisla oddelene medzerou:\n");
	scanf("%d %d", &x, &y);

	sucet(px, py, ps);

	printf("sucet cisiel je: %d", s);
	


	return 0;
}