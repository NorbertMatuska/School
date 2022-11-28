#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int nacitaj(float *x, float *y) {

	printf("zadajte cisla:\n");
	scanf("%f %f", x, y);

	return 0;
}

int vypocitaj(float x, float y, float *add_obv, float *add_obs) {

	*add_obv = 2 * (x + y);
	*add_obs = (x * y);

	return 0;
}

int main() {

	float a = 0, b = 0;
	float obv = 0, obs = 0;

	nacitaj(&a, &b);
	vypocitaj(a, b, &obv, &obs);

	printf("obvod: %.3f\nobsah: %.3f\n", obv, obs);


	return 0;
}