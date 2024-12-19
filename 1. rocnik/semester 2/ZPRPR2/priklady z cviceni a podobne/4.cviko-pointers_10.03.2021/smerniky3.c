#include <stdio.h>
#include <stdlib.h>
#define ROZSAH 80

// najdenie minimalneho prvku pola, a vratenie jeho ADRESY !! 
 double* addrMinArray(double pole[], int pocet)
//double* addrMinArray(double *pole, int pocet)
{
	
	// implementacia cez indexy
	int i, minIndex = 0;	
	for (i = 1; i < pocet; i++)
	  if (pole[minIndex] > pole[i])
	    minIndex = i;
	return &(pole[minIndex]);
	
	
	/*
	// implementacia cez smerniky
	int i;
	double *minAddr = &(pole[0]);  
	// int *minAddr;
	// minAddr = &(pole[0]);
	
	for (i = 1; i < pocet; i++)
	  if (*minAddr > pole[i])
	    minAddr = &(pole[i]);
	return minAddr;
	*/
}



int main(void)
{
  double pole [ROZSAH];
  int n, i;
  double *p = NULL;
  
  scanf	("%d", &n);
  
  if (n >= ROZSAH)
  {
  	// chyba rozsahu vstupu
  	return -1;
  }
  
  for (i = 0; i < n; i++)
  {
    scanf("%lf", &(pole[i]));		
  }	

  // najdeme prvok s minimalnou hodnotou a vratime jeho adresu
  p = addrMinArray(pole, n);
  
  printf("Minimalny prvok pola je %lf na adrese %d\n", *p, p);
  
  
  // dokonca vieme zistit, kolkaty je to prvok pola z bazickej adresy pola a adresy prvku
  // smerniky vsak musia mat spravny typ !!!  
  printf("index minimalneho prvku v poli je %d\n", p - &(pole[0])); // da sa zapisat aj jednoduchsie ako (p - pole)

  // pokial by sme vsak mali vseobecne smerniky (alebo smerniky roznych typov, treba realizovat prepocet)
  

printf("index minimalneho prvku v poli je %d\n", ((void *)p - (void *)pole) / sizeof(double)); 

// bez zohladnenia typov smernikov (pouziti vseobecneho smernika void* nam rozdiel jednoducho urci iba pocet bytov..  )
// teda nie index prvku, preto treba byt opatrny, nemiesat typy smernikov, a pri akychkolvek odchylkach dosledne pretypovavat
printf("pocet bytov od zaciatku pola po minimalny prvok v poli je %d\n", ((void *) p - (void *) pole) ); 


	
  return 0;
}
