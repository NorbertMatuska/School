//CV1 uloha 4
//Norbert Matuška

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

        int N, k = 0, q = 0, fflush(FILE * stream);
        double num1 = 0, num;
        printf("Zadajte pocet clenov postupnosti\n");
        scanf_s("%d", &N);
        fflush;
        for (int i = 0; i < N; i++) {
            printf("Zadajte hodnotu clena %d \n", (i + 1));
            scanf_s("%lf", &num);
            fflush;
            if (num1 == 0) { num1 = num; continue; }
            if ((num1 * 2) < num || (num1 / 2) > num) {
                printf("\nPostupnost je nespravna");
                break;
            }
            q++;
            if (i == N - 1) { printf("\nPostupnost je spravna"); }
            num1 = num;
        }

	return 0;
}