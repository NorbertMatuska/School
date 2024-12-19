#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 5


vytvorpole(int* x, int* pole) {

    if (*x % 2 == 1) {

        for (int i = 0; i < SIZE; i++) {
            pole[i] = 73 + (i * 2);
        }

    }
    else if (*x % 2 == 0) {

        for (int i = 0; i < SIZE; i++) {
            pole[i] = 32 + (i * 2);
        }
    }


}

int main() {

    int x, pole[5];
    printf("Zadajte cele cislo:\n");
    scanf_s("%d", &x);

    vytvorpole(&x, pole);

    for (int i = 0; i < SIZE; i++) {
        printf("%d \n", pole[i]);
    }

    return 0;
}