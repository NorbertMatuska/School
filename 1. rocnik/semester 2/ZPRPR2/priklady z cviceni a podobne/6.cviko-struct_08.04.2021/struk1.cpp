#include <stdio.h>
#include <string.h>

struct osoba  // definujeme novy zlozeny typ osoba
{             // ten bude obsahovat viacere polozky roznych typov
  int vek;           
  double hmotnost;
  char meno[41];  // vsetky premenne su aktualne staticke
  int vyska;    
};




// funkcia na vypis vsetkych poloziek danej premennej typu osoba
void vypisOsoby (struct osoba person)  
{
  printf("\nMeno a Priezvisko : %s\n", person.meno);
  printf("vek osoby : %d\n", person.vek);
  printf("hmotnost osoby : %lf\n", person.hmotnost);
  return;
}





int main(void)
{
	 int a,b;
	
	
  struct osoba tomas, lucia;

  tomas.vek = 21;
  tomas.hmotnost = 78.2;
  tomas.vyska = 182;
  // tomas.meno = "Tomas Hrasko";   // NOO !!!!! Retazec sa musi kopirovat funkciou strcpy/strncpy
  strncpy(tomas.meno, "Tomas Hrasko", 41);  // kopirujem retazec do statickeho pola

  lucia.vek = 19;
  strncpy(lucia.meno, "Lucia Novakova", 41);  
  lucia.hmotnost = 59.4;
  lucia.vyska = 178;    

  vypisOsoby(lucia);
  vypisOsoby(tomas);

  // vsetko sme doteraz robili statickymi premennymi, preto nie je potrebne uvolnovat pamat
  return 0;
}
