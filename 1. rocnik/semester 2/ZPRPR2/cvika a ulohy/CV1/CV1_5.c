//CV1 uloha 5 
//Norbert Matuška

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

    int N;

    scanf_s("%d", &N);

    if (N < 1 || N > 15) { printf("Cislo nie je z daneho intervalu\n"); return 0; }
    for (int i = 1; i <= N; i++) {
        printf("%d: ", i);
        for (int k = (N - (i - 1)); k >= 1; k--) printf("%d  ", k);
        printf("\n");
    }

	return 0;
}