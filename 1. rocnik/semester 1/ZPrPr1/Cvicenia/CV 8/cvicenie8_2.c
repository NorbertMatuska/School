//FIIT STU
//Norbert Matu�ka
//6/12/2020
//cvicenie 8
//uloha 3

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int arr[50], len, i = 1, tp = 0, tmp = 0, cmp[11] = { 0,10,20,30,40,50,60,70,80,90,100 };
    char input[100], * token, out[10][50], temp[20];
    printf("zadajte vstupne hodnoty postupnosti");
    gets(input);
    len = strlen(input);
    token = strtok(input, " ");
    arr[0] = atoi(token);
    while (token != NULL) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            arr[i] = atoi(token);
        }
        i++;
    }

    for (int k = 0; k < 10; k++) {
        tmp = 0;
        for (int q = 0; q < i; q++) {
            tp = 0;
            if (arr[q] > cmp[k] && arr[q] < cmp[k + 1]) {
                tmp++;
                if (tmp == 1) {
                    printf("\n%d | ", k);
                }
                tp = arr[q] - cmp[k];
                printf("%d", tp);
            }
        }
    }

    return 0;
}