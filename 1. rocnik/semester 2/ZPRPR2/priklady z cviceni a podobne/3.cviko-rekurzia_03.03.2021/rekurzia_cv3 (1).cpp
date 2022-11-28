#include<stdio.h>


/*
Nacitajte zo vstupu cislo n (cele kladne cislo).
Vypocitajte sucet cisiel 1 + 2 + 4 + 8 + 16 + 32 + ...  az po posledne cislo mensie alebo rovne n. 
Vypiste vysledok na obrazovku, ako aj do zatvorky uvedte jednotlive scitavane cisla v poradi od najvacsieho).
Vypocet realizujte rekurzivne !

Priklad vstupu: 
23
Vystup: 
(16 + 8 + 4 + 2 + 1) = 31

*/


// rekurzivna funkcia na vypocet sumy mocnin 2
int rek_suma(int x, int hranica)
{  
  if (x > hranica)
    return 0;
  
  // printf("%d ", x); 
  int pom = rek_suma(2*x, hranica);  // volanie vnorenej funkcie
  printf("%d", x);
  if (x > 1)  // podmienka na zabezpecenie , aby sa "+" vypisalo len medzi dvojicou cisiel 
    printf(" + ");
  return x+pom;
}


int main(void)
{
  int n, sucet;
  scanf("%d", &n);

  printf("(");
  sucet = rek_suma(1, n); // rekurziu v tomto pripade volame s 2 parametrami, 1. aktualna iteracia, 2. horna hranica
  printf(") = %d", sucet);
}

