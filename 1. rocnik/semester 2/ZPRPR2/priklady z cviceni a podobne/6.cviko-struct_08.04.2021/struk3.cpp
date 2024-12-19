#include <stdio.h>
#include <string.h>


struct osoba
{
  int vek;
  double hmotnost;
  char meno[41];
  int vyska;  
  double bmi;  
};



void vypocitajBMIosobe3(struct osoba *person)
{
   // (*smernik).polozka    je ekvivalentne s     smernik->polozka 

  if (person == NULL)
    return;

  // 1. sposob zapisu 
  double vyska = (*person).vyska / 100.0;	
  (*person).bmi = (*person).hmotnost / (vyska * vyska);   // je mozne pouzit aj person->bmi = ... 
  printf("Funkcia vypocitajBMIosobe() %s %lf \n", (*person).meno, (*person).bmi);  
	
/*	
  // 2. sposob zapisu  
  double vyska = person->vyska / 100.0;	
  person->bmi = person->hmotnost / (vyska * vyska);
  printf("Funkcia vypocitajBMIosobe3() %s %lf \n", person->meno, person->bmi);
*/
  return;
}




void vypisOsoby (struct osoba person)
{
  printf("\nMeno a Priezvisko : %s\n", person.meno);
  printf("vek osoby : %d\n", person.vek);
  printf("hmotnost osoby : %lf\n", person.hmotnost);
  printf("BMI osoby : %8.3lf\n\n", person.bmi);
  return;
}





int main(void)
{
  struct osoba tomas, lucia;

  tomas.vek = 21;
  tomas.hmotnost = 78.2;
  tomas.vyska = 182;
  strncpy(tomas.meno, "Tomas Hrasko", 40);

  lucia.vek = 19;
  strncpy(lucia.meno, "Lucia Novakova", 40);
  lucia.hmotnost = 59.4;
  lucia.vyska = 178;
  

  vypocitajBMIosobe3(&tomas);
  vypocitajBMIosobe3(&lucia);


  vypisOsoby(tomas);
  vypisOsoby(lucia);
  

  return 0;
}
