#include <stdio.h>

int minArray(int pole[], int pocet)
{
	int i, min = pole[0];
	for (i = 1; i < pocet; i++)
	  if (min > pole[i])
	    min = pole[i];
	
	return min;
}

int maxArray(int pole[], int pocet)
{
	int i, max = pole[0];
	for (i = 1; i < pocet; i++)
	  if (max < pole[i])
	    max = pole[i];
	
	return max;
}

// funkcia vypocita minimum a maximum pola prvkov, a vrati ich cez vstupne parametre 
int minmaxArray(int pole[], int pocet, int *minim, int *maxim)
{
	int i, min = pole[0], max = pole[0];
	for (i = 1; i < pocet; i++)
    {
    	if (min > pole[i])
    	  min = pole[i];
    	if (max < pole[i])
		  max = pole[i];  
	}
	
	// vysledne hodnoty minima a maxima zapiseme na pridelene adresy
	// a tym zabezpecime vystup funkcie
	if (minim != NULL)
	  *minim = min;
	if (maxim)
	  *maxim = max;
	  
   	if ((minim == NULL) || (maxim == NULL))
	   return -1;
	else
	   return 0;     
}


#define ROZSAH 80


int main(void)
{
  int n, pole [ROZSAH];
  int i, min1, max1;
  
  
  scanf	("%d", &n);
  
  if (n > ROZSAH)
  {
  	// chyba rozsahu vstupu
  	return -1;
  }
  
  for (i = 0; i < n; i++)
  {
    scanf("%d", &(pole[i]));		
  }	
	

  // vyhladanie minima a maxima z pola o n prvkoch	
  min1 = minArray(pole, n);
  max1 = maxArray(pole, n);  
  printf("min = %d\nmax = %d\n", min1, max1);
  
  
  // druhy sposob, funkcia vrati min a max cez vstupne parametre pouzitim smernikov
  if (minmaxArray(pole, n, &min1, &max1) == 0)	
    printf("min = %d\nmax = %d\n", min1, max1);	
	
  return 0;
}
