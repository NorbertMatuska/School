#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {

    char meno[52];
    char adresa[102];
    int start;
    int end;

    struct person* next;

}PERSON, * P_PERSON;

typedef struct izba {
    int cisloizb;
    int pocetlo;
    double cena;

    P_PERSON firstPerson;

    struct izba* next;
}IZBA, * P_IZBA;

P_IZBA createStructI(int cisloizb, int pocetlo, double cena) {

    P_IZBA add = (P_IZBA)malloc(sizeof(IZBA));
    add->next = NULL;
    add->firstPerson = NULL;

    add->cisloizb = cisloizb;
    add->pocetlo = pocetlo;
    add->cena = cena;

    return add;
}

P_PERSON createStructP(char* meno, char* adresa, int start, int end) {

    P_PERSON add = (P_PERSON)malloc(sizeof(PERSON));
    add->next = NULL;

    strcpy(add->meno, meno);
    strcpy(add->adresa, adresa);
    add->start = start;
    add->end = end;

    return add;
}


void n(FILE** hotel, P_IZBA* first) {
    int izbypoc = 0;
    P_IZBA docasi; //do docasi a docasp ukladam "docasne" vytvoreny struct pre izbu/osobu
    P_PERSON docasp;
    if(*hotel == NULL) { //kontrolujem, ci *hotel nieje nahodou uz otvoreny aby som ho neotvaral viackrat
        *hotel = fopen("hotel.txt", "r+");
        if (*hotel == NULL) {
            printf("Zaznamy neboli nacitane\n");
            exit(-1);
        }
    }
    rewind(*hotel);

    char tmp[102];
    int tempcislo;
    int temppocet;
    double tempcena;
    char tempmeno[52];
    char tempadresa[102];
    int tempstart;
    int tempend;

    P_IZBA tmpi; //do tmpi ukladam pointer na prvu node v linked liste

    while (!feof(*hotel)) {
        fgets(tmp, 102, *hotel);
        //tmp[strcspn(tmp, "\n")] = 0;
        if ( ! strtok(tmp, "\r\n") ) strtok(tmp, "\n");
        if (strcmp(tmp, "---") == 0) {  //pomocou podmienok kontrolujem, ci mam zobrat osobu alebo izbu
            fscanf(*hotel, "%d %d %lf", &tempcislo, &temppocet, &tempcena);
            docasi = createStructI(tempcislo, temppocet, tempcena); //funkcia na vytvorenie structu pre jednu izbu
            if (*first == NULL) {
                *first = docasi;
            }
            else {
                tmpi = *first;
                while (tmpi->next != NULL) {
                    tmpi = tmpi->next;
                }
                tmpi->next = docasi;
            }
            izbypoc++;
        }
        else if (strcmp(tmp, "#") == 0) {
            fgets(tempmeno, 52, *hotel);
            //tempmeno[strcspn(tempmeno, "\n")] = 0;
            if ( ! strtok(tempmeno, "\r\n") ) strtok(tempmeno, "\n");
            fgets(tempadresa, 102, *hotel);
            //tempadresa[strcspn(tempadresa, "\n")] = 0;
            if ( ! strtok(tempadresa, "\r\n") ) strtok(tempadresa, "\n");
            fscanf(*hotel, "%d %d", &tempstart, &tempend);
            //printf("%s%s%d\n%d\n", tempmeno, tempadresa, tempstart, tempend);
            if (docasi->firstPerson == NULL) {
                docasi->firstPerson = createStructP(tempmeno, tempadresa, tempstart, tempend);
            }
            else {
                docasp = docasi->firstPerson;
                while (docasp->next != NULL) {
                    docasp = docasp->next;
                }
                docasp->next = createStructP(tempmeno, tempadresa, tempstart, tempend);
            }
        }

    }
    printf("Nacitalo sa %d zaznamov\n", izbypoc);

    fclose(*hotel);
    *hotel = NULL;
};

void v(P_IZBA first) {  //jednoducha funkcia na vypis

    for (P_IZBA curr = first; curr != NULL; curr = curr->next) {
        printf("Izba cislo: %d\nPocet lozok: %d\nCena: %.2lf\nZoznam hosti: \n", curr->cisloizb, curr->pocetlo, curr->cena);
        for (P_PERSON currP = curr->firstPerson; currP != NULL; currP = currP->next) {
            printf("Meno: %s\nAdresa: %s\nZaciatok rezervacie: %d\nKoniec rezervacie: %d\n", currP->meno, currP->adresa, currP->start, currP->end);
            if (currP->next != NULL) {
                printf("############################\n");
            }
        }
        if (curr->next != NULL) {
            printf("----------------------------\n");
            printf("----------------------------\n");
        }
    }

}

void r(FILE** hotel, P_IZBA* first) {

    int tempcislo, temppocet, tempstart, tempend, x;
    double tempcena;
    char tempmeno[52], tempadresa[102];
    P_IZBA docasi;
    P_PERSON docasp;
    P_IZBA curr;
    //P_PERSON currP;
    if(*hotel == NULL) {
        *hotel = fopen("hotel.txt", "a+");
        if (*hotel == NULL) {
            printf("Situacia bez presneho zadania.\n");
            return;
        }
    }

    scanf(" %d", &tempcislo);
    scanf(" %d", &temppocet);
    scanf(" %lf", &tempcena);
    scanf(" %d", &x);
    fprintf(*hotel, "---\n%d\n%d\n%.2lf\n", tempcislo, temppocet, tempcena);

    curr = *first;
    docasi = createStructI(tempcislo, temppocet, tempcena);
    if (curr == NULL) {     //zistujem ci sa nacitali zdroje s n, ak nie, vytvorim novy struct na zaciatok linked listu
        curr = docasi;
        *first = curr;
    }
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        if (curr->next == NULL) {
            curr->next = docasi;
        }
    }

    for (int i = 0; i < x; i++) {
        scanf(" %[^\n]", tempmeno);
        scanf(" %[^\n]", tempadresa);
        scanf(" %d", &tempstart);
        scanf(" %d", &tempend);
        fprintf(*hotel, "#\n%s\n%s\n%d\n%d\n", tempmeno, tempadresa, tempstart, tempend);
        if(docasi->firstPerson == NULL) {
            docasi->firstPerson = createStructP(tempmeno, tempadresa, tempstart, tempend);

            }
        else {
            docasp = docasi->firstPerson;
            while(docasp->next != NULL) {
                docasp = docasp->next;
            }
            docasp->next = createStructP(tempmeno,tempadresa, tempstart, tempend);
        }

        /*if (curr->firstPerson == NULL) {
            curr->firstPerson = createStructP(tempmeno, tempadresa, tempstart, tempend);
            //currP = docasp;
            printf("currP was null\n");
        }

        else if (curr->firstPerson->next == NULL) {
            curr->firstPerson->next = createStructP(tempmeno, tempadresa, tempstart, tempend);
            //currP->next = docasp;
            printf("created person\n");
        }*/
    }
    rewind(*hotel);
    fclose(*hotel);
    *hotel = NULL;
}

void z() {

}

void h(P_IZBA first, FILE **hotel) {
    int input = 0;
    P_IZBA curr = NULL;
    P_PERSON currP = NULL;
    if(*hotel == NULL) {
        *hotel = fopen("hotel.txt", "r");
        if (*hotel == NULL) {
            printf("Situacia bez presneho zadania.\n");
            return;
        }
    }
    char pom[102];
    int izbypoc = 0;
    while(!feof(*hotel)) {
        fgets(pom, 102, *hotel);
        //pom[strcspn(pom, "\n")] = 0;
        if ( ! strtok(pom, "\r\n") ) strtok(pom, "\n");
        if(strcmp(pom, "---") == 0) {
            izbypoc++;

        }
        else {
            pom[0] = '\0';
        }
    }
    //printf("%d\n", izbypoc);

    scanf(" %d", &input);
    //printf("%d\n", input);
    curr = first;
    int *numbers = (int*) malloc(izbypoc*sizeof(int));
    int i = 0;
    while(curr != NULL) {
        currP = curr->firstPerson;
        while (currP != NULL) {

            if(currP->start <= input && currP->end >= input) {
                numbers[i] = curr->cisloizb;
                i++;
                break;
            }
            currP = currP->next;
        }
        curr = curr->next;
    }
    if(i > 0) { //ak sa nasla aspon jedna zhoda, bubble sort na vzostupne zoradovanie cisiel
        int temp, x, y, z;
        for (y = 0; y < i; y++) {
            for (z = y + 1; z < i; z++) {
                if (numbers[y] > numbers[z]) {
                    temp = numbers[z];
                    numbers[y] = numbers[z];
                    numbers[z] = temp;
                }
            }
        }
        for (x = 0; x < i; x++) {
            printf("%d\n", numbers[x]);
        }
    }
    else {
        printf("K datumu %d neevidujeme rezervaciu\n", input);
    }

    free(numbers);
    fclose(*hotel);
    *hotel = NULL;
}

void a (P_IZBA *first, FILE **hotel) {

    int inputizba, inputlozko;
    P_IZBA curr;
    P_PERSON currP;
    if(*first != NULL) { //najprv skontrolujem ci sa vobec vytvoril linked list

        if(*hotel == NULL) {
        *hotel = fopen("hotel.txt", "w"); //ak by nebol este vytvoreny, fopen v mode w by mi vymazalo cely subor a nic nezapisalo
        if (*hotel == NULL) {
            printf("Situacia bez presneho zadania.\n");
            return;
        }
    }
    scanf(" %d", &inputizba);
    scanf(" %d", &inputlozko);
        curr = *first;
        while (curr != NULL) {
            if (curr->cisloizb == inputizba) {
                curr->pocetlo = inputlozko; //najde zhodu, zapise a vyjde z loopu
                break;
            }
            curr = curr->next;
        }
        curr = *first;
        while (curr != NULL) { //prepise cely subor uz s aktualizovanym poctom lozok
            //printf("---\n%d\n%d\n%.2lf\n", curr->cisloizb, curr->pocetlo, curr->cena);
            fprintf(*hotel, "---\n%d\n%d\n%.2lf\n", curr->cisloizb, curr->pocetlo, curr->cena);
            currP = curr->firstPerson;
            while (currP != NULL) {
                //printf("#\n%s\n%s\n%d\n%d\n", currP->meno, currP->adresa, currP->start, currP->end);
                fprintf(*hotel, "#\n%s\n%s\n%d\n%d\n", currP->meno, currP->adresa, currP->start, currP->end);
                currP = currP->next;
            }
            curr = curr->next;
        }
    printf("Izba cislo %d ma lozkovu kapacitu %d.\n", inputizba, inputlozko);
    fclose(*hotel);
    *hotel = NULL;
    }
}

void k(P_IZBA *first) {

    if (first != NULL) {
        P_IZBA tmp = *first;
        P_PERSON tmpp;
        while (tmp != NULL) {
            P_IZBA pomocny = tmp;
            tmp = tmp->next;
            tmpp = pomocny->firstPerson;
            while(tmpp != NULL) {
                P_PERSON pomocna = tmpp;
                tmpp = tmpp->next;
                free(pomocna);
            }
            free(pomocny);
        }
        *first = NULL;
    }
}

int main() {

    FILE* hotel = NULL;
    P_IZBA first = NULL;
    int continu = 1;
    char x = 0;

    while (continu) {
        scanf(" %c", &x);
        switch (x) {
            case 'n':
                if (first != NULL) {
                    k(&first); //ak linked list nieje prazdny, treba ho vynulovat a nasledne znova naplnit
                    n(&hotel, &first);
                }
                else{
                    n(&hotel, &first);
                }
                break;
            case 'v':
                v(first);
                break;
            case 'r':
                r(&hotel, &first);
                break;
            case 'h' :
                h(first, &hotel);
                break;
            case 'a' :
                a(&first, &hotel);
                break;
            case 'k' :
                k(&first);
                continu = 0;
                break;
            default:
                break;
        }
    }
    hotel = NULL;
    return 0;
}
