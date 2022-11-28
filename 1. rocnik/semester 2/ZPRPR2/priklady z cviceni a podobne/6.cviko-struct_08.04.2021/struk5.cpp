#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct osoba
{
  char meno[31];
  int vek;
  double hmotnost; 
  int vyska;  
  struct osoba *next;  
};


void vypis1(struct osoba person)
{ 
  printf("--------------------------------------------\n");
  printf("Adresa tohto prvku Hexadecimalne %X\n", &person);
  printf("--------------------------------------------\n");
  printf("Meno osoby : %s\n", person.meno); 
  printf("vek osoby : %d\n", person.vek);
  printf("hmotnost osoby : %lf\n", person.hmotnost);
  printf("vyska osoby : %d\n", person.vyska); 
  printf("[Adresa dalsieho prvku spajaneho zoznamu Hexadecimalne ] %X\n", person.next);
  printf("--------------------------------------------\n\n");
  return;
}


void vypis2 (struct osoba * person)
{ 
  if (person == NULL)
    return;

  printf("--------------------------------------------\n");
  printf("Adresa tohto prvku Hexadecimalne %X\n", person);
  printf("--------------------------------------------\n");
  printf("Meno osoby : %s\n", person->meno); 
  printf("vek osoby : %d\n", person->vek);
  printf("hmotnost osoby : %lf\n", person->hmotnost);
  printf("vyska osoby : %d\n", person->vyska); 
  printf("[Adresa dalsieho prvku spajaneho zoznamu Hexadecimalne] %X\n", person->next);
  printf("--------------------------------------------\n\n\n");
  return;
}




// vytvori novu dynamicku premennu typu osoba
struct osoba * VytvorOsobu(int vekO, double hmotnostO, int vyskaO, const char *menoO)
{
  struct osoba *pom;	

  pom = (struct osoba *) malloc (sizeof (struct osoba));
  if (pom == NULL)
    return NULL;

  pom->vek = vekO;
  pom->hmotnost = hmotnostO;
  pom->vyska = vyskaO;
  strncpy(pom->meno, menoO, 31);
  pom-> next = NULL;
  return pom;
}


#define POCET_OSOB 10


int main(void)
{
  struct osoba *first = NULL; // iniciovanie prazdneho spajaneho zoznamu

  	
  // naplnenie spajaneho zoznamu 
  first = VytvorOsobu(29, 61, 178, "Jozko Mrkvicka");
  first->next = VytvorOsobu(31, 68, 185, "Adam Sangala");
  first->next->next = VytvorOsobu(19, 62, 169, "Michaela Schumacherova");
  
  // samozrejme v projekte c. 2 moze byt vo vstupnom subore vela zaznamov, takze to treba urcite riesit cyklom 
  // treba preto nejaky pomocny smernik (napr. struct osoba *help), 
  // ktory bude ukazovat napr. vzdy na posledny platny zaznam spajaneho zoznamu
  // a pri pridavani na koniec zoznamu sa novy zaznam "zavesi" na jeho smernik next;  ( help->next = VytvorOsobu(...);   help=help->next;  ) 



  // vypis spajaneho zoznamu
  // tu je jednoduchy priklad, ako pomocou cyklu prechadzat spajanym zoznamom, pouzitim pomocneho smernika pomocny
  struct osoba *pomocny = first;
  while (pomocny)
  {	
    // uloha na zamyslenie sa, co sa zmeni ak namiesto volania funkcie vypis2() pouzijem vypis1() 
    // (teda pouzijem zakomentovany riadok) ??
	  // vypis1(*pomocny);  
	   vypis2(pomocny);  // vypis aktulneho prvku spajaneho zoznamu
  
    
   pomocny = pomocny->next;  // posun na dalsi prvok spajaneho zoznamu
   
   // pomocny = (*pomocny).next;
  }

  

  // uvolnenie spajaneho zoznamu
  // treba kazdy prvok spajaneho zoznamu uvolnit samostatne
  // toto opat bude potrebne v projekte riesit v cykle ! 
  free(first->next->next);
  free(first->next);
  free(first);
  
  first = NULL;
  
  return 0;
}
