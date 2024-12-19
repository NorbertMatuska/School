#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int v (FILE **tovar, FILE **dodavatelia) {
    *tovar = fopen("tovar.txt", "r+");

    if (*tovar == NULL) {
        printf("Subor sa nepodarilo otvorit\n");
        return -1;
    }

    *dodavatelia = fopen("dodavatelia.txt", "r+");
    if (*dodavatelia == NULL) {
        printf("Subor sa nepodarilo otvorit\n");
        return -1;
    }

    char nazov[52], meno[52], adresa[52];
    int pocet, idt, idd;
    double cena, hmotnost;

    //while loop na ziskanie vsetkych zaznamov zo suboru a zaroven ich aj printnut nech nemusime dynamicky alokovat
    while (!feof(*tovar)){
        fgets(nazov, 52, *tovar);
        nazov[strcspn(nazov, "\n")] = 0;
        printf("Nazov tovaru: %s\n", nazov);
        fscanf(*tovar, "%d %lf %lf %d ", &pocet, &cena, &hmotnost, &idt);
        printf("Pocet kusov na sklade: %d\nCena: %.2lf\nHmotnost: %.4lf\nID dodavatela: %d\n\n", pocet, cena, hmotnost, idt);
    }

    printf("----------------------------------------------------------------------------------------\n----------------------------------------------------------------------------------------\n");

    //ten isty while loop len pre dodavatelov
    while(!feof(*dodavatelia)) {
        fscanf(*dodavatelia, "%d ", &idd);
        printf("ID dodavatela: %d\n", idd);
        fgets(meno, 52, *dodavatelia);
        meno[strcspn(meno, "\n")] = 0;
        printf("Meno dodavatela: %s\n", meno);
        fgets(adresa, 52, *dodavatelia);
        adresa[strcspn(adresa, "\n")] = 0;
        printf("Adresa dodavatela: %s\n", adresa);
        printf("\n");
    }
    //rewind na konci kazdej funkcie ktora pracuje so suborom
    rewind(*tovar);
    rewind(*dodavatelia);
    return 0;
}

void o (FILE **tovar) {
    char tempnazovt[52], nazovt[52];
    int idt;
    double cena, tempcena[50], porovnanie = 0;
    int x = 0;
    int i = 0, inputcheck = 0;
    if (scanf(" %d", &x) == 1) { //check pre return value scanf ci uzivatel zadal cislo a nie pismeno
        while (!feof(*tovar)) {
            fscanf(*tovar, "%s %*d %lf %*lf %d ", nazovt, &cena, &idt); //loop ktory naskenuje do temp premennych udaje z file
            if (idt == x) { //a porovnava ci sa id zhoduje so vstupom dodavatela
                tempcena[i] = cena;
                if (tempcena[i] > porovnanie) { //porovna ci je cena vacsia ako predosleho tovaru od dodavatela
                    porovnanie = tempcena[i];
                    strcpy(tempnazovt, nazovt); //ak ano pomocou strcpy skopiruje nazov tovaru
                    inputcheck++;
                }
            }

            i++;
        }
        if (inputcheck != 0) { //ak sa nenasla zhoda, nic nevypise
            printf("Najdrahsi tovar je: %s\n", tempnazovt);
        }
    }
    rewind(*tovar);
}

int n(FILE **tovar, FILE **dodavatelia, char ***nazovt, int **pocett, double **cenat, double **hmotnost, int **idt, int* zaznamy, int **idd, char ***menod, char ***adresa, int *zaznamyd) {

    char c;
    int count = 0;
    c = getc(*tovar);
    while (c != EOF){
        if (c == '\n') { // inkrementuje count ked najde newline char
            count = count + 1;
        }
        c = getc(*tovar);
    }
    *zaznamy = (count + 2)/6; //loop na pocitanie mi vzdy napocita o jeden riadok menej takze si pridam +2 aby som vypocital pocet zaznamov
    *nazovt =(char**) malloc((*zaznamy) * sizeof(char*));

    for (int i = 0; i < (*zaznamy); i++) {
        (*nazovt)[i] = (char *) malloc(52 * sizeof(char)); //52 kvoli \0 \n
    }
    *pocett = (int*) malloc((*zaznamy) * sizeof(int));
    *cenat = (double*) malloc((*zaznamy) * sizeof(double));
    *hmotnost = (double*) malloc((*zaznamy) * sizeof(double));
    *idt = (int*) malloc((*zaznamy) * sizeof(int));

    rewind(*tovar);
    int i = 0;
    while (!feof(*tovar)) {
        fgets((*nazovt)[i], 52, *tovar);
        (*nazovt)[i][strcspn((*nazovt)[i], "\n")] = 0; //vrati vsetky charaktery ktore nenaslo (cize vsetko okrem newline)
        fscanf(*tovar, "%d %lf %lf %d ", &(*pocett)[i], &(*cenat)[i], &(*hmotnost)[i], &(*idt)[i]);
        i++;
    }

    char c1;
    int count1 = 0;
    c1 = getc(*dodavatelia);
    while (c1 != EOF){
        if (c1 == '\n') { // Ikrementuje count1 ked najde newline char
            count1 = count1 + 1;
        }
        c1 = getc(*dodavatelia);
    }
    *zaznamyd = (count1 + 2)/4;

    *idd = (int*) malloc((*zaznamyd) * sizeof(int));
    *menod =(char**) malloc((*zaznamyd) * sizeof(char*));

    for (int z = 0; z < (*zaznamyd); z++) {
        (*menod)[z] = (char *) malloc(52 * sizeof(char)); //52 kvoli \0 \n
    }
    *adresa =(char**) malloc((*zaznamyd) * sizeof(char*));

    for (int y= 0; y < (*zaznamyd); y++) {
        (*adresa)[y] = (char *) malloc(52 * sizeof(char)); //52 kvoli \0 \n
    }

    rewind(*dodavatelia);
    int n = 0;
    while (!feof(*dodavatelia)) {
        fscanf(*dodavatelia, "%d ", &(*idd)[n]);
        fgets((*menod)[n], 52, *dodavatelia);
        (*menod)[n][strcspn((*menod)[n], "\n")] = 0;
        fgets((*adresa)[n], 52, *dodavatelia);
        (*adresa)[n][strcspn((*adresa)[n], "\n")] = 0;
        n++;
    }

    rewind(*tovar);
    rewind(*dodavatelia);
    return 0;
}

void s(char **nazovt, int *pocett, int *idt, int *zaznamy) {
    int x = 0, i;
    if(*nazovt == NULL || pocett == NULL || idt == NULL) { //check ci sa vytvorili polia
        printf("Polia nie su vytvorene\n");
        exit(0);
    }
    scanf(" %d", &x);

    for (i = 0; i < *zaznamy; i++) {//hlada zhodu id pri kazdom tovare od dodavatela a nasledne vypise
        if (idt[i] == x) {
            printf("%s (%d na sklade)\n", nazovt[i], pocett[i]);
        }
    }

}

void h (int *pocett, int *zaznamy) { //nefunkcne a netusim preco, riesil som to dlho a skusal vsetko ale nejde to
    int prva = 0, druha = 0, tretia = 0, stvrta = 0, piata = 0, siesta = 0, siedma = 0, osma = 0, deviata = 0, desiata = 0;

    if(pocett == NULL) {
        printf("Polia nie su vytvorene\n");
        exit(0);
    }
    for (int i = 0; i <= *zaznamy; i++) {
        if (0 < *(&pocett)[i] && *(&pocett)[i] < 9) {
            prva++;
        }
        else if(10 < *(&pocett)[i] && *(&pocett)[i] < 19) {
            druha++;
        }
        else if(20 < *(&pocett)[i] && *(&pocett)[i] < 29) {
            tretia++;
        }
        else if(30 < *(&pocett)[i] && *(&pocett)[i] < 39) {
            stvrta++;
        }
        else if(40 < *(&pocett)[i] && *(&pocett)[i] < 49) {
            piata++;
        }
        else if(50 < *(&pocett)[i] && *(&pocett)[i] < 59) {
            siesta++;
        }
        else if(60 < *(&pocett)[i] && *(&pocett)[i] < 69) {
            siedma++;
        }
        else if(70 < *(&pocett)[i] && *(&pocett)[i] < 79) {
            osma++;
        }
        else if(80 < *(&pocett)[i] && *(&pocett)[i] < 89) {
            deviata++;
        }
        else if(90 < *(&pocett)[i] && *(&pocett)[i] < 99) {
            desiata++;
        }
    }
    printf("<0,9>: %d\n<10,19>: %d\n<20,29>: %d\n<30,39>: %d\n<40,49>: %d\n<50,59>: %d\n<60,69>: %d\n<70,79>: %d\n<80,89>: %d\n<90,99>: %d\n", prva, druha, tretia, stvrta, piata, siesta, siedma, osma, deviata, desiata);
}

void p (FILE **tovar, char **nazovt, int *pocett, double *cenat, double *hmotnost, int *idt, int *zaznamy) {
    char nazovinput[50];
    int pocetinput = 0;
    scanf(" %[^\n]", nazovinput);
    scanf(" %d", &pocetinput);

    for (int i = 0; i < *zaznamy; i++) {
        if (strcmp(nazovinput, nazovt[i]) == 0) { //hlada zhodu nazvu tovaru podla return value strcmp
            pocett[i] = pocetinput;
            printf("Aktualny poctu kusov na sklade tovar %s je: %d\n", nazovt[i], pocett[i]);
            for (int k = 0; k < *zaznamy; k++) { //prepise cely subor nanovo uz aj s novym poctom tovaru
                fprintf(*tovar, "%s\n%d\n%.2lf\n%.4lf\n%d\n\n", nazovt[k], pocett[k], cenat[k], hmotnost[k], idt[k]);
            }
            break;
        }
    }
}

void z (char **nazovt, double *hmotnost, int *zaznamy) {
    double x = 0, y = 0;
    //double sort[*zaznamy]; <- snazil som sa spravit nejaku mudru funkciu na sort ale nevydarilo sa
    scanf(" %lf", &x);
    scanf("%lf", &y);
    if(x > y) {
        printf("Prve cislo musi byt mensie ako druhe cislo\n");
        exit(0);
    }

    for(int i = 0; i < *zaznamy; i++) { //hlada zhodu a zaroven vypisuje
        if (x < hmotnost[i] && hmotnost[i] < y) {
            printf("%s\n", nazovt[i]);
        }
    }
}

void k (FILE **tovar, FILE **dodavatelia, char **nazovt, int *pocett, double *cenat, double *hmotnost, int *idt, int *idd, char **menod, char **adresa) {
    free(nazovt);
    free(cenat);
    free(hmotnost);
    free(idt);
    free(pocett);
    free(idd);
    free(menod);
    free(adresa);
    fclose(*tovar);
    fclose(*dodavatelia);
}

int main()
{
    FILE *tovar = NULL, *dodavatelia = NULL;
    char **nazovt = NULL, **menod = NULL, **adresa = NULL;
    char x = 0;
    int *pocett = NULL, *idt = NULL, *idd = NULL, zaznamy=0, zaznamyd=0;
    double *hmotnost = NULL, *cenat = NULL;
    int pokracovat = 1;
    while (pokracovat) {
        scanf(" %c", &x);
        switch (x) {
            case 'v' :
                v(&tovar, &dodavatelia);
                break;
            case 'o' :
                o(&tovar);
                break;
            case 'n' :
                n(&tovar, &dodavatelia, &nazovt, &pocett, &cenat, &hmotnost, &idt, &zaznamy, &idd, &menod, &adresa, &zaznamyd);
                break;
            case 's' :
                s(nazovt, pocett, idt, &zaznamy);
                break;
            case 'h' :
                h(pocett, &zaznamy);
                break;
            case 'p' :
                p(&tovar, nazovt, pocett, cenat, hmotnost, idt, &zaznamy);
                break;
            case 'z' :
                z(nazovt, hmotnost, &zaznamy);
                break;
            case 'k' :
                k(&tovar, &dodavatelia, nazovt, pocett, cenat, hmotnost, idt, idd, menod, adresa);
                pokracovat = 0;
                break;
            default:
                //printf("Nespravne zadane\n");
                break;
        }
    }


    return 0;
}