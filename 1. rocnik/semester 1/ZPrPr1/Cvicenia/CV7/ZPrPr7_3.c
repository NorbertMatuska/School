#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void vynasob(int* xa, int* xb, int* xs) {

	printf("Zadaj 2. cele cislo:\n");
	scanf("%d", &*xb);

	

	*xs = *xa * *xb;
	
}

int main() {

	int a, b, s;
	int* ya;
	int* yb;
	int* ys;

	ya = &a;
	yb = &b;
	ys = &s;

	printf("Zadaj 1. cele cislo:\n");
	scanf("%d", &a);

	vynasob(ya, yb, ys);

	printf("%d", s);


	return 0;
}