#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct osoba
{
  int vek;
  double hmotnost; 
  int vyska;  
  double bmi;    
};





void generujOsoby(struct osoba *p_per, int count)
{
  if (p_per == NULL)
    return;

  for (int i = 0; i < count; i++)
  {  
    p_per[i].vek = 10+i;
    p_per[i].hmotnost = 30+20*i;  
    p_per[i].vyska = 100+10*i;
  }
}


void vypocitajBMIosobe(struct osoba *person)
{	
 
  double vyska = person->vyska / 100.0;	
  person->bmi = person->hmotnost / (vyska * vyska);
  printf("Funkcia vypocitajBMIosobe() %lf \n", person->bmi);
  return;
}




void vypisOsoby (struct osoba person)
{  
  printf("vek osoby : %d\n", person.vek);
  printf("hmotnost osoby : %lf\n", person.hmotnost);
  printf("vyska osoby : %d\n", person.vyska);
  printf("BMI osoby : %8.3lf\n\n", person.bmi);
  return;
}


#define POCET_OSOB 10


int main(void)
{
	
	
  printf("\n\npraca so statickym polom struktur !!\n\n\n");

  // pouzijeme staticke pole osob a pracujeme s nim
  struct osoba persons[POCET_OSOB];  
  generujOsoby(persons, POCET_OSOB);

  for (int i = 0; i < POCET_OSOB; i++)
  {
	  vypocitajBMIosobe(&(persons[i]));
	  vypisOsoby(persons[i]);
  }
 


  printf("\n\npraca s dynamickym polom struktur !!\n\n\n");

  // pouzijeme dynamicke pole osob, a pracujeme s nim

  struct osoba *d_persons = NULL;
  d_persons = (struct osoba *)malloc(POCET_OSOB * sizeof(struct osoba));

  if (!d_persons) 
  {
	  // chyba, alokacia bola neuspesna
    printf("chyba pri alokacii pamate\n");
    return -1;
  }

  generujOsoby(persons, POCET_OSOB);

  for (int i = 0; i < POCET_OSOB; i++)
  {
	  vypocitajBMIosobe(&(persons[i]));
	  vypisOsoby(persons[i]);
  }
 


 
  free(d_persons); // kedze je pole dynamicke, tak ho musime aj uvolnit 
  // jednotlive polozky pola su vsak staticke, preto nie je potrebne volat free pre kazdu osobu 
  // (inak povedane, je to 1-rozmerne dynamicke pole prvkov typu struct osoba)

  return 0;
}
