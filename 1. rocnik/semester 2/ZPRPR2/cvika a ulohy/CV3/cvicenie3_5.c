#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() 
{

    int n, i, j, r, s;

    scanf("%d %d %d", &n, &r, &s);

    if ((n >= 1 && n <= 15) && n % 2 == 1 && (r >= 1 && r <= 7) && (s >= 1 && s <= 7))
    {
        for (int k = 1; k <= s; k++)
        {
            for (i = 1; i <= n; i++)
            {
                for (int l = 1; l <= r; l++)
                {
                    for (j = 1; j <= n; j++)
                    {
                        if (i == j || i == n / 2 + 1 || j == n / 2 + 1 || j == n + 1 - i)
                        {
                            printf("*");
                        }

                        else printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }

    else
    {
        printf("Zly vstup\n");
    }
    return 0;
}