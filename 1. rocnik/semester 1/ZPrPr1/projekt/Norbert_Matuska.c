#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funckia read nam precita cely subor
//Princip funkcie void read() som sa naucil od spoluziaka @lukasm96 a pomenil som to k vlastnemu vyuzitiu
//zdroj: https://drive.google.com/drive/folders/1jySDGg5cFi70TfSHN_N6uQCE1mx8GsnE?usp=sharing
void read(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int *number_of_racers) {

    FILE* jazdci;
    char lines[500], * substring; //zadefinujem si ze riadkov v subore moze byt 500
    int n_racers = 0;
    int i;
    char *lastname;

    //treba nam otvorit subor
    jazdci = fopen("jazdci.csv", "r");

    //kontrola ci sa nam subor otvoril
    if (jazdci == NULL) {
        printf("file couldnt be opened correctly or it doesnt exist\n");
        return;
    }

    while (fgets(lines, 500, jazdci)) {
        
        substring = strtok(lines, ";"); //precita meno a skonci pri medzere
        strcpy(name[n_racers], substring); //prekopiruje udaje z substring do name

        /*substring = strtok(NULL, ";"); //podobny princip
        strcpy(surname[n_racers], substring);*/
        
        lastname = strrchr(substring, ' ');
        strcpy(surname[n_racers], (lastname + 1));
        //printf("%s\n", surname[n_racers]);

        substring = strtok(NULL, ";");
        sex[n_racers] = substring[0]; //cita jeden znak z nultej pozicie 

        substring = strtok(NULL, ";");
        birth[n_racers] = atoi(substring); //atoi nam string prehodi na integer

        substring = strtok(NULL, ";");
        strcpy(car[n_racers], substring);

        for (i = 0; i < 5; i++) {
            substring = strtok(NULL, ";");
            round_times[n_racers][i] = atof(substring);
        }
        n_racers++; //aby sme vedeli kolko mame jazdcov
    }
    *number_of_racers = n_racers;
    fclose(jazdci);
}

void sum(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int* number_of_racers) {
    int current_racer = 0, current_round = 0;

    for (current_racer; current_racer < *number_of_racers; current_racer++) {
        printf("%s, nar. %d, %c, Automobil: %s\n", name[current_racer], birth[current_racer], sex[current_racer], car[current_racer]);
        /*printf("\nNAME AND SURNAME: %s %s\n", name[current_racer], surname[current_racer]);
        printf("SEX: %c\n", sex[current_racer]);
        printf("YEAR OF BIRTH: %d\n", birth[current_racer]);
        printf("BRAND: %s\n", car[current_racer]);*/
        
        current_round = 0;

        for (current_round; current_round < 5; current_round++) {
            printf("%.3f;", round_times[current_racer][current_round]);
        }
        printf("\n");
    }
}

void driver(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int* number_of_racers) {
    char temp[25];
    int d = 0, tempo = 0, k;
    double max, min;

    fseek(stdin, 0, SEEK_END);

    printf("input surname:\n");
    
    gets(temp);
    
    for (int i = 0; i < *number_of_racers; i++) {
        //printf(" %s %s\n", temp, surname[i]);
        
        //ak temp == surname[i]
            //vypis
            //koniec cyklu

        if (strcmp(temp, surname[i]) == 0) {

            //printf("podarilo sa\n");
            printf("\n");
            printf("%s\nnar. %d, %c\nautomobil: %s\n\n", name[i], birth[i], sex[i], car[i]);

            min = max = round_times[i][0];
            for (k = 1; k < 5; k++) {
                if (max < round_times[i][k]) {
                    max = round_times[i][k];
                }
                else if (min > round_times[i][k]) {
                    min = round_times[i][k];
                }
            }
            printf("Najlepsie kolo: %.3f\nNajhorsie kolo: %.3f\n", min, max);
            //(1. kolo + 2.kolo + 3.kolo + 4.kolo + 5.kolo) / pocet kol = avg;
            printf("Priemerny cas kola je %.3f\n", (round_times[i][0] + round_times[i][1] + round_times[i][2] + round_times[i][3] + round_times[i][4]) / 5);
            printf("-\n");
            break;
        }


        /*NEFUNGOVALO :(
        d = 0;

        for (int r = 0; r < 4; r++) {
            printf(" %c %c\n", temp[r], surname[i][r]);

            if (surname[i][r] == temp[i]) {
                
                printf("Succes\n");
                d++;
                if (d == 4) {
                    tempo = i;
                    printf("%s naslo sa meno\n", surname[i]);
                }
            }

            

        }*/

        
    }
    //fseek(stdin, 0, SEEK_END);
}

void lap(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int* number_of_racers) {
    int d = 0, temp = 0, k;
    double max;

    max = round_times[0][0];
    for (int i = 0; i < *number_of_racers; i++) {
        for (k = 0; k < 5; k++) {
            if (round_times[i][k] < max) {
                max = round_times[i][k];
                d = k + 1;
                temp = i;
            }
        }
    }

    printf("Najlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n", max, name[temp], d);
    printf("-\n");
}

void gender(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int* number_of_racers) {
    int i = 0, k = 0, d = 0, temp = 0;
    char s = 0;
    double max = 100;

    printf("Zadajte pohlavie m/f (male/female)\n");
    scanf(" %c", &s,1); //nacitavam 1 byte

    fseek(stdin, 0, SEEK_SET);

    if (s == 'm') {
        //printf("Je to chlapec!!\n");
        for (i = 0; i < *number_of_racers; i++) {
            if (sex[i] == 'm') {
                for (k = 0; k < 5; k++) {
                    if (round_times[i][k] < max) {
                        max = round_times[i][k];
                        d = k + 1;
                        temp = i;
                    }
                }
            }
        }
        printf("Najlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n", max, name[temp], d);
        printf("-\n");
    }
    else if (s == 'f') {
        //printf("Je to dzivka\n");
        for (i = 0; i < *number_of_racers; i++) {
            if (sex[i] == 'f') {
                for (k = 0; k < 5; k++) {
                    if (round_times[i][k] < max) {
                        max = round_times[i][k];
                        d = k + 1;
                        temp = i;
                    }
                }
            }
        }
        printf("Najlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n", max, name[temp], d);
        printf("-\n");
    }
    else {
        printf("wrong input\n");
    }
}

void brand(char name[50][25], char surname[50][25], char* sex, int* birth, char car[50][25], double round_times[50][5], int* number_of_racers) {
    int i = 0, k = 0;
    int tempf, tempb, temph, tempp, df, db, dh, dp;
    double maxf = 100, maxb = 100, maxh = 100, maxp = 100;
    char znacky[8][25] = { "ferrari", "Ferrari", "bugatti", "Bugatti", "honda", "Honda", "porsche", "Porsche"}; 

    //printf("%s %s\n", znacky[0], znacky[1]);

    for (i = 0; i < *number_of_racers; i++) {
        //printf("%s\n", car[i]);
        if (strcmp(znacky[0], car[i]) == 0) {
            //printf("succes");
            for (k = 0; k < 5; k++) {
                if (round_times[i][k] < maxf) {
                    maxf = round_times[i][k];
                    tempf = i;
                    df = k + 1;
                }
            }
        }

        if (strcmp(znacky[2], car[i]) == 0) {
            for (k = 0; k < 5; k++) {
                if (round_times[i][k] < maxb) {
                    maxb = round_times[i][k];
                    tempb = i;
                    db = k + 1;
                }
            }
        }

        /*if (strcmp(znacky[4], car[i]) == 0) {
            for (k = 0; k < 5; k++) {
                if (round_times[i][k] < maxh) {
                    maxh = round_times[i][k];
                    temph = i;
                    dh = k + 1;
                }
            }
        }*/

        if (strcmp(znacky[6], car[i]) == 0) {
            for (k = 0; k < 5; k++) {
                if (round_times[i][k] < maxp) {
                    maxp = round_times[i][k];
                    tempp = i;
                    dp = k + 1;
                }
            }
        }
    }

    printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znacky[0], maxf, name[tempf], df);
    printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znacky[2], maxb, name[tempb], db);
    //printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n\n", znacky[4], maxh, name[temph], dh);
    printf("Znacka: %s\nNajlepsie kolo: %.3f\nJazdec: %s\nCislo kola: %d\n", znacky[6], maxp, name[tempp], dp);
    printf("-\n");
}

void year(char name[50][25], char surname[50][25], char* sex, int* birth, char car[50][25], double round_times[50][5], int* number_of_racers) {
    int i = 0, k = 0, temp = 0, d = 0, check = 0;
    int year;
    double max;
    
    printf("Zadajte rok (YYYY):\n");
    scanf("%d", &year);
    max = 100;
    for (i = 0; i < *number_of_racers; i++) {
        //printf("%d\n", birth[i]);
        if (birth[i] < year) {
            //printf("succes\n");
            for (k = 0; k < 5; k++) {
                if (round_times[i][k] < max) {
                    max = round_times[i][k];
                    temp = i;
                    d = k + 1;
                    check++;
                }
            }
        }
    }
    if (check != 0) {
        printf("%s\nnar. %d\nNajlepsie kolo: %.3f\nCislo kola: %d\n", name[temp], birth[temp], max, d);
        printf("-\n");
    }
    else {
        printf("wrong input\n");
    }
}

void average(char name[50][25], char surname[50][25], char* sex, int* birth, char car[50][25], double round_times[50][5], int* number_of_racers) {
    int i = 0;
    double avg[50], max;
    int temp;
    
    temp = 0;
    max = avg[0] = (round_times[0][0] + round_times[0][1] + round_times[0][2] + round_times[0][3] + round_times[0][4]) / 5;
    printf("%s - %.3f\n", name[0], avg[0]);
    for (i = 1; i < *number_of_racers; i++) {
       
        avg[i] = (round_times[i][0] + round_times[i][1] + round_times[i][2] + round_times[i][3] + round_times[i][4]) / 5;
        printf("%s - %.3f\n", name[i], avg[i]);

        if (avg[i] < max) {
            max = avg[i];
            temp = i;
        }
    }

    /*for (i = 0; i < *number_of_racers; i++) {
        
        temp = 0;
        max = avg[0];
        if (max < avg[i]) {
            max = avg[i];
            temp = i;
        }

    }*/
    printf("\n");
    printf("Najlepsie:\n%s - %.3f\n", name[temp], max);
    printf("-\n");

}

void under(char name[50][25], char surname[50][25], char* sex, int* birth, char car[50][25], double round_times[50][5], int* number_of_racers) {
    double cas;
    int i = 0, k = 0;
    int temp;
    //int temp[50][5];

    printf("Zadajte cas (maximalne tri desatinne cisla)\n");
    scanf("%lf", &cas);

    for (i = 0; i < *number_of_racers; i++) {
        temp = 0;
        for (k = 0; k < 5; k++) {
            if (round_times[i][k] < cas) {
                temp++;   
            }
        }
        if (temp != 0) {
            printf("\n%s ", name[i]);
            if (temp == 1) {
                printf("%d kolo, ", temp);
            }
            else if (temp > 1 && temp < 5) {
                printf("%d kola, ", temp);
            }
            else {
                printf("%d kol, ", temp);
            }
        }
        for (k = 0; k < 5; k++) {
            if (round_times[i][k] < cas) {
                printf("%d %.3f ",k + 1, round_times[i][k]);
            }
        }
    }
    if (temp == 0) {
        printf("nenasiel sa pozadovany cas podla zadanych kriterii alebo wrong input\n");
    }
    printf("\n-\n");
}

/*void change() {
    
}*/

void newDriver(char name[50][25], char surname[50][25], char* sex, int* birth, char car[50][25], double* round_times, int* number_of_racers) {
    int tempbirth = 0, i, check = 1, temp = 0;
    char tempname[25], tempsurname[25], tempsex, carcheck[25], tempcar[25];
    double rounds[5];
    char znacky[8][25] = { "ferrari", "Ferrari", "bugatti", "Bugatti", "honda", "Honda", "porsche", "Porsche" };


    printf("\nenter name of the driver\n");
    gets(tempname);

    printf("enter surname of the driver\n");
    gets(tempsurname);

    while (check) {
        printf("enter brand of the drivers car\n");
        gets(carcheck);
        for (i = 0; i < 8; i++) {
            if (strcmp(carcheck, znacky[i]) == 0) {
                strcpy(tempcar, carcheck);
                temp++;
            }
        }
        if (temp != 0) {
            check = 0;
            break;
        }
        else {
            printf("wrong input!\nplease enter a valid brand\n");
        }
    }
    
    printf("enter the year of drivers birth\n");
    scanf(" %d", &tempbirth);

    check = 1;
    while (check) {
        printf("enter gender of the driver\n");
        scanf(" %c", &tempsex);
        if (tempsex == 'm' || tempsex == 'f') {
            check = 0;
            break;
        }
        else {
            printf("wrong input!\ntry again\n");
        }
    }

    for (i = 0; i < 5; i++) {
        printf("enter time of the %d. round\n", i + 1);
        scanf(" %lf", &rounds[i]);
    }
    printf("\nadding the following data:\n\n");
    if (tempsex == 'm') {
        printf("name: %s\nsurname: %s\ngender: male\nbirth: %d\ncar brand: %s\n", tempname, tempsurname, tempbirth, tempcar);
        for (i = 0; i < 5; i++) {
            printf("round no.%d: %.3f\n", i + 1, rounds[i]);
        }
    }
    else {
        printf("name: %s\nsurname: %s\ngender: female\nbirth: %d\ncar brand: %s\n", tempname, tempsurname, tempbirth, tempcar);
        for (i = 0; i < 5; i++) {
            printf("round no.%d: %.3f\n", i + 1, rounds[i]);
        }
    }
    printf("-\n");

    FILE* jazdci;
    jazdci = fopen("jazdci.csv", "a");

    if (jazdci == NULL) {
        printf("file couldnt be opened correctly or it doesnt exist\n");
        return;
    }

    fprintf(jazdci, "\n%s %s;%c;%d;%s;%.3f;%.3f;%.3f;%.3f;%.3f", tempname, tempsurname, tempsex, tempbirth, tempcar, rounds[0], rounds[1], rounds[2], rounds[3], rounds[4]);
    fclose(jazdci);
}

/*rmdriver mi pokazilo cely den, tak aspon za snahu nejake bezvyznamne + :( */

void rmdriver(char name[50][25], char surname[50][25], char sex[50], int birth[50], char car[50][25], double round_times[50][5], int* number_of_racers) {
    int tempbirth[50], check = 0, i = 0, r = 0, temp = *number_of_racers;
    char tempname[50][25], tempsurname[50][25], tempsex[50], tempcar[50][25];
    double rounds[50][5];

    //printf("%.3f", round_times[1][3]);

    printf("zadajte jazdca, ktoreho chcete vymazat\n");
    gets(tempsurname);

    for (i = 0; i < *number_of_racers; i++) {
        if (strcmp(tempsurname, surname[i]) == 0) {
            check++;
            continue;
        }
        else if (check != 0 && i == 0) {
            strcpy(tempname[i], name[i]);
            tempsex[i] = sex[i];
            tempbirth[i] = birth[i];
            strcpy(tempcar[i], car[i]);
            for (r = 0; r < 5; r++) {
                rounds[i][r] = round_times[i][r];
            }
        }
        else if (check != 0 && i != 0) {
            strcpy(tempname[i - 1], name[i]);
            tempsex[i - 1] = sex[i];
            tempbirth[i - 1] = birth[i];
            strcpy(tempcar[i - 1], car[i]);
            for (r = 0; r < 5; i++) {
                rounds[i - 1][r] = round_times[i][r];
            }
        }
        else {
            strcpy(tempname[i], name[i]);
            tempsex[i] = sex[i];
            tempbirth[i] = birth[i];
            strcpy(tempcar[i], car[i]);
            for (r = 0; r < 5; r++) {
                rounds[i][r] = round_times[i][r];
            }
        }
    }
    for (int k = 0; k < temp - 1; k++) {
        printf("%s;%c;%d;%s\n", tempname[k], tempsex[k], tempbirth[k], tempcar[k]);
        printf("%.3f\;%.3f\;%.3f\;%.3f\;%.3f\n", rounds[k][0], rounds[k][1], rounds[k][2], rounds[k][3], rounds[k][4]);
    }

    FILE* jazdci;
    jazdci = fopen("jazdci.csv", "w");

    if (jazdci == NULL) {
        printf("file couldnt be opened correctly or it doesnt exist\n");
        return;
    }
    //fprintf(jazdci, "%s;%c;%d;%s", tempname[0], tempsex[0], tempbirth[0], tempcar[0]);
    for (int k = 0; k < temp - 1; k++) {
        fprintf(jazdci, "%s;%c;%d;%s;", tempname[k], tempsex[k], tempbirth[k], tempcar[k]);
        fprintf(jazdci, "%.3f\;%.3f\;%.3f\;%.3f\;%.3f\n", rounds[k][0], rounds[k][1], rounds[k][2], rounds[k][3], rounds[k][4]);
    }
    fclose(jazdci);
}

/*int sizepole() {
    //kontrola poctu riadkov
    FILE* jazdci;
    int i, s = 1; //size = s
    while ((i = fgetc(jazdci)) != EOF) {
        if (i == '\n') {
            s++;
        }
    }
    printf("pocet riadkov v subore je %d", s);
    return 0;
}*/

void menu() {

    char name[50][25];
    char surname[50][25];
    char sex[50];
    int birth[50];
    char car[50][25];
    double round_times[50][5];
    int number_of_racers = 0;

    int pokracovat = 1;
    char x;
    
    while (pokracovat) {
        printf("s Vypis hodnot\n");
        printf("d Vypis hodnot - podla priezviska\n");
        printf("l Vypis najlepsieho kola - celkovo\n");
        printf("g Vypis najlepsieho kola - pohlavie\n");
        printf("b Vypis najlepsieho kola - znacka\n");
        printf("y Vypis najlepsieho kola - starsi ako zadany rok\n");
        printf("a Vypis najlepsieho priemerneho kola\n");
        printf("u Vypis jazdcov, ktori dali kolo pod nejaky cas\n");
        printf("c Prepisanie hodnoty nejakeho kola - COMING SOON\n");
        printf("n Pridanie noveho jazdca a zadanie hodnot\n");
        printf("r Vymazanie jazdca - COMING SOON\n");
        printf("x Ukoncenie programu\n");
        printf("\n");
        
        fseek(stdin, 0, SEEK_SET); //Vyriesilo to moj problem s nacitanim viacero znakov za sebou a nerozbilo to program tak som to takto nechal
        scanf(" %c", &x);
        fseek(stdin, 0, SEEK_SET);

        read(name, surname, sex, birth, car, round_times, &number_of_racers);

        switch (x) {

        case 's':
            
            read(name, surname, sex, birth, car, round_times, &number_of_racers);
            sum(name, surname, sex, birth, car, round_times, &number_of_racers);
            
            break;
        
        case 'd':

            
            driver(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;
        
        case 'l':

            lap(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'g':

            gender(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'b':

            brand(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'y':

            year(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'a':

            average(name, surname, sex, birth, car, round_times, &number_of_racers);

            break;

        case 'u':

            under(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'c':

            break;

        case 'n':

            newDriver(name, surname, &sex, &birth, car, &round_times, &number_of_racers);
            read(name, surname, sex, birth, car, round_times, &number_of_racers);
            sum(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'r':
            //rmdriver(name, surname, sex, birth, car, round_times, &number_of_racers);
            break;

        case 'x':

            pokracovat = 0;
            break;

        default:

            printf("Nespravne zadane\n");
            break;
        }
    }


}

int main() {

    menu();

	return 0;
}