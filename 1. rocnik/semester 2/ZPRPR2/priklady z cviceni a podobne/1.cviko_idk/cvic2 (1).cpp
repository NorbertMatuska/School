#define _CRT_SECURE_NO_WARNINGS


/*
Vzorovy priklad na cv. c. 2
Priklad na temy: zaokruhlovanie, nacitavanie, vypis, priradenie, ascii kody, podmienky, aritmeticke operacie

*/



#include <stdio.h>    // scanf, printf
#include <math.h>     // floor, ceil, sqrt


int main(void)
{
int i, j;
double x;
float y;
char c;
int mensie, vacsie;


scanf("%d %d", &i, &j);   // nacitame 2 cele cisla



// symbol % reprezentuje zvysok po celociselnom deleni
if ((i % 5) == 0) // POZOR   == sluzi na porovnanie  , zatial co  = je priradenie
{
printf("cislo %d je delitelne 5. \n", i);       // testovanie delitelnosti 5
}
else
{
printf("cislo %d nie je delitelne 5. \n", i);
}

printf("sucin cisiel %d a %d je %d\n", i, j, i * j);
printf("podiel cisiel %d a %d je %lf\n", i, j, ((double)i) / j);   // podiel cisiel (realny)
printf("celociselny podiel cisiel %d a %d je %d\n", i, j, i / j);  // celociselny podiel

if (j != 0)
  printf("Zvysok po deleni cisla %d cislom %d je %d\n", i, j, i % j);

printf("ASCII kodu %d zodpoveda znak %c\n", i, i);               // znak vs ascii kod


// aplikovanie ternarneho operatora pre urcenie mensieho a vacsieho cisla  
mensie = (i < j ? i : j);



vacsie = (i > j ? i : j);

printf("minimum z dvojice cisiel %d a %d je %d\n", i, j, mensie);
printf("maximum z dvojice cisiel %d a %d je %d\n\n", i, j, vacsie);





scanf("%lf %f", &x, &y);  // nacitame 2 realne cisla ; pozn. desatinny oddelovac je reprezentovany znakom .  

printf("%lf zaokruhlene nadol je %d alebo tiez %.0lf\n", x, (int)x, floor(x));  // zaokruhlenie nadol
printf("%lf zaokruhlene nahor je %.0lf\n", x, ceil(x));                         // zaokruhlenie nahor

// aritmeticke zaokruhlenie (pripocitam 0.5 a pouzijem zaokruhlenie nadol)
printf("%lf zaokruhlene aritmeticky je %d alebo %.0lf \n", x, (int)(x + 0.5), floor(x + 0.5));









printf("Sucin cisiel %lf a %f je cislo %lf\n", x, y, x * y);
if (1e-20 < fabs(y)) // testujem ci y nie je priliz blizke nule (funkcia fabs() vrati absolutnu hodnotu realneho cisla)
printf("Podiel cisiel %lf a %f zaokruhleny na 3 miesta je cislo %.3lf\n", x, y, x / y);  // aritmeticke zaokruhlovanie na 3 desatinne miesta




if (x >= 0.0)
printf("Odmocnina z cisla %lf je %lf\n", x, sqrt(x));   // vypocet odmocniny


    


 // priklad zlozenej podmienky , na otestovanie ci x patri do intervalu (i, j)
if ((mensie < x) && (x < vacsie))   // jedna sa o otvoreny interval, preto su tam < , v pripade uzavreteho intervalu by sme pouzili <=  
printf("Cislo %lf patri do intervalu (%d, %d)\n", x, mensie, vacsie);
else
printf("Cislo %lf nepatri do intervalu (%d, %d)\n", x, mensie, vacsie);


scanf(" %c", &c);
printf("ASCII KOD %d zodpoveda znaku %c\n", c, c);                 // znak vs ascii kod

printf("znak %c (ASCII %d) posunuty o %d dava znak %c (ASCII %d)\n", c, c, i, c + i, c + i);  // posun znaku o i (vyssi ascii kod)



/*
int a = 5;
a = a + 1;
a++;
++a;
int z;
z = 5*(++a);
a = a + 1;
z = 5*(a);

a = a + 1;
a++;
a = a - 1;
a--;  */


return 0;
}
