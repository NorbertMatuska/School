#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

void kvadraticka(double a, double b, double c) {

    double d1, d2, d;

    d = (b * b) - (4 * a * c);
    d = sqrt(d);

    d1 = (-b + d) / (2 * a);
    d2 = (-b - d) / (2 * a);

    printf("korene rovnice: \n x1 = %.3f \n x2 = %.3f", d1, d2);
}

int main() {

    double a, b, c;

    scanf("%lf %lf %lf", &a, &b, &c);
    kvadraticka(a, b, c);

    return 0;
}