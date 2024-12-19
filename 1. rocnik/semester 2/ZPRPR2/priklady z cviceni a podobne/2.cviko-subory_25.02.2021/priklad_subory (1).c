#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
	FILE *fin, *fout;
	
	int velke = 0, male = 0;
	int ok;
	char znak;
	
	// r - read , w - write, a - append
	fin = fopen("vstupnySubor.txt", "r");  // otvorenie suboru na citanie
	
	if (fin == NULL)
	  return -1;
	  
	do
	{
	  ok = fscanf(fin, "%c", &znak);
	  
	  if (ok != 1)
	    break;
	    
	  if ((znak >= 'a') && (znak <= 'z'))   // testovanie maleho pismena
	    male++;
	  if ((znak >= 'A') && (znak <= 'Z'))
	    velke++;	 
	
	} while (1);
	
    fclose (fin);   // uzavretie suboru 
	
	fout = fopen("vystupnySubor.txt","w");  // otvorenie suboru na zapis
	if (fout == NULL)   // test otvorenia suboru
      return -2;
	  
	  	
	for (int i = 1; i <= 10; i++)
	{
	  fprintf(fout, "%3d,%3d,%3d,%12.6lf\n", i, i*male, i*velke, exp(i));	  // zapis do suboru
	}  	
	
	if (fclose(fout) == 0)
	  printf("Data boli uspesne zapisane do suboru");
	
		  
	return 0;
	
	

}


/*
scanf()  fscanf()   sscanf()

printf() fprintf()  sprintf()



getch()  getchar()  fgets() gets()  getc()

putchar()  putc()   puts()
*/









