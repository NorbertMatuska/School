#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int zlomok(int c, int m) {
    int gcd;

    while (c != 0) {
        gcd = m % c;
        m = c;
        c = gcd;

    }
    gcd = m;
    return gcd;
}
int main() {
    int c, m, del;
    printf("Zadajte dve cele cisla do zlomku\n");
    scanf("%d %d", &c, &m);
    del = zlomok(c, m);
    printf("\nZakladny tvar zlomku: %d/%d", (c / del), (m / del));
    return 0;
}