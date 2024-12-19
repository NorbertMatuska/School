#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i, pocet;
	scanf("%d", &pocet);
	
	// ROZHODNE NIE: float p[pocet] !!!!!!!!!!!!!
	
	float *p;
	
	// alokovanie dynamickeho pola realnych cisiel
	p = (float *)                      // po pouziti funkcie malloc(), calloc(), ci realloc() je nutne smernik pretypovat !
	   malloc(pocet * sizeof(float));  // tato * je obycajne nasobenie
	
	if (p == NULL)  // nedoradilo sa alokovat pole (system nam odmietol pridelit pamat)
	  return -1;
	
	// nasledne mozeme pracovat s polom, v podstate tak, ako keby bolo staticke.. jednoduchym pouzivanim []
	// s dodrzanim rozsahu indexov    0 ... pocet-1
	// hlavne si nesmiem premennu pocet prepisat, lebo nebudem vediet po aku poziciu mozem s polom pracovat. 
	
	for (i = 0; i < pocet; i++)
    {  
      //scanf("%f", &(p[i]));	
	  // da sa to zapisovat aj v symbolickej smernikovej aritmetike v tvare
	  scanf("%f", p+i);	
    }
	
	// ...
	
	for (i = 0; i < pocet; i++)
    {  
      printf("%f \t%d\n", p[i], &(p[i]));	
    }
	
	printf("\n1 premenna typu float zabera bytov : %d \n\n", sizeof(float));
	
	// uvolnenie pola pamate
	free(p);
	
	
	return 0;
}
