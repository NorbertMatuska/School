//CV 1 uloha 1
//Norbert Matuška

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	double kg, cm, m, bmi;

	printf("zadajte dve realne cisla s jednym desatinnym miestom predstavujuce vysku v cm a hmotnost v kg oddelene jednou medzerou:\n");
	scanf_s(" %lf %lf", &cm, &kg);
	printf("%.1lf %.1lf", cm, kg);
	m = cm / 100;
	printf("%.1lf\n", m);
	bmi = kg / (m * m);

	printf("BMI: %.3lf", bmi);

	return 0;
}