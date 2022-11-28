#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() 
{

    int n, i, j;

    scanf("%d", &n);

    if ((n >= 1 && n <= 15) && n % 2 == 1) {

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (i == j || i == n / 2 + 1 || j == n / 2 + 1 || j == n + 1 - i) {
                    printf("*");
                }
                else printf(" ");
            }
            printf("\n");
        }
    }

    else
    {
        printf("Zly vstup\n");
    }

    return 0;
}
