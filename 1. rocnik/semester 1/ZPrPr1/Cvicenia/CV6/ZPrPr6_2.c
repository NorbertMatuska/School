#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int nasobky(int* x, int xcount, int* y, int k) {
    int ycount = 0;
    for (int i = 0; i < xcount; i++) {
        if ((x[i] % k) == 0) {
            y[ycount] = x[i];
            ycount++;
        }
    }
    printf("Pocet y: %d \n", ycount);
    printf("y:{");
    for (int p = 0; p < ycount; p++) {
        printf("%d,", y[p]);
    }
    printf("}");
    return ycount;
}


int main()
{
    int y[10], x[10] = { 4, 7, 10, 1, 3, 9, 2, 5, 8, 6 }, xcount = 10, k = 2;
    int ycount = nasobky(x, xcount, y, k);
    return 0;
}
