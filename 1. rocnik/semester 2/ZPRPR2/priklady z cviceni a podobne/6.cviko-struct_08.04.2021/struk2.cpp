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



// sice sa hodnota bmi vypocita, a spravne vypise, avsak do mainu sa nedostane
// pretoze cela prememenna person je iba kopiou povodnej premennej tomas / lucia
// cize bmi sa vypocita iba v novej kopii, ktora sa nevrati do mainu
void vypocitajBMIosobe(struct osoba person)
{
  double vyska = person.vyska / 100.0;	
  person.bmi = person.hmotnost / (vyska * vyska);
  printf("Funkcia vypocitajBMIosobe() %s %lf \n", person.meno, person.bmi);
  return;
}


// takto to uz fungovat bude, pokial hodnotu aj vratim, a v maine ju priradim 
struct osoba vypocitajBMIosobe2(struct osoba person)
{
  double vyska = person.vyska / 100.0;	
  person.bmi = person.hmotnost / (vyska * vyska);
  
  printf("Funkcia vypocitajBMIosobe2 %s %lf \n", person.meno, person.bmi);
  return person;	
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
  strncpy(tomas.meno, "Tomas Hrasko", 41);


  lucia.vek = 19;
  strncpy(lucia.meno, "Lucia Novakova", 41);
  lucia.hmotnost = 59.4;
  lucia.vyska = 178;
  

  vypocitajBMIosobe(tomas);
  vypocitajBMIosobe(lucia);

  vypisOsoby(tomas);
  vypisOsoby(lucia);
  

  tomas = vypocitajBMIosobe2(tomas);
  lucia = vypocitajBMIosobe2(lucia);

  vypisOsoby(tomas);
  vypisOsoby(lucia);


  return 0;
}
