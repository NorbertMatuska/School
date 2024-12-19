#include <stdio.h>



// SMERNIKY = UKAZOVATELE = POINTERY

int main(void)
{
	// &    premenna -> adresu
	// *    adresy   -> premennu
	
	
	int n;
	int *s = NULL;  // nulovanie smernika na int
	
	// int *s;  // ekvivalentne s riadkom 14
	// s = NULL;
	
	scanf("%d", &n);
	
	printf("Hodnota n : %8d   Adresa n: %8d\n",  n, &n);
	
	
	// *s = n; // toto este nemozeme urobit, lebo smernik neobsahuje ziadnu platnu adresu !!! 
	// dokonca ani keby sme na zaciatku smernik nevynulovali, aj tak je stale adresa neplatna, lebo nie je alokovana
	
	s = &n;  // smernik nasmerujeme na adresu premennej n
	// smernik uz teda obsahuje platnu adresu alokovanej premennej (staticky alokovanej)
	printf("Hodnota s : %8d   Adresa s: %8d\n",  s, &s);
	
	
	// kedze smernik ukazuje na premennu n, mozeme preto napr. docielit, upravu hodnoty premennej n 
	// bez toho , aby sme pracovali priamo s nou
	
	(*s) ++; // cize zvysim hodnotu na adrese v smerniku s (co zodpoveda premennej n)
	// *s = *s + 1 ;
	printf("Hodnota n : %8d   Adresa n: %8d\n",  n, &n); // cize hodnota sa zmenila, adresa nie 
	


	printf("\n\nAdresa n Hexadecimalne : %x   alebo %X\n\n\a",  &n, &n);
	
	return 0;
	
}
