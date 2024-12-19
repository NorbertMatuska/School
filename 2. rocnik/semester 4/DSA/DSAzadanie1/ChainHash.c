//
// Created by 42190 on 3/19/2022.
//

#include "ChainHash.h"

typedef struct chain {
    int num;
    struct chain *next;
} CHAIN, *PCHAIN;

typedef struct tableChain {
    PCHAIN *table;
    int size;
    int elementsNum;
} TABLECHAIN, *PTABLECHAIN;

//funkcia na najdenie prvocisla
int findPrime(int x) {
    if (x <= 1) {
        return 0;
    }
    if (x <= 3) {
        return 1;
    }
    if (x % 2 == 0 || x % 3 == 0) {
        return 0;
    }
    for (int i = 5; i * i <= x; i = i + 6) {
        if (x % i == 0 || x%(i+2) == 0) {
            return 0;
        }
    }
    return 1;
}
// funkcia na najdenie dalsieho najblizsieho prvocisla
int findNextPrime(int x) {
    if (x <= 1) {
        return 2;
    }
    int prime = x;
    int gotPrime = 0;
    while(!gotPrime) {
        prime++;
        if(findPrime(prime)) {
            gotPrime = 1;
        }
    }
    return prime;
}

void insertChain(PTABLECHAIN info, int num) {
    int funcHash = num % info->size;
    PCHAIN *chainTable = info->table;
    info->elementsNum++;
    PCHAIN temp;
    PCHAIN last = chainTable[funcHash];

    if (chainTable[funcHash] == NULL) {
        chainTable[funcHash] = malloc(sizeof(CHAIN));
        chainTable[funcHash]->num = num;
        chainTable[funcHash]->next = NULL;
    }
    else {
        temp = malloc(sizeof(CHAIN));
        temp->num = num;
        temp->next = NULL;
        while (last->next != NULL) {
            if(last->num == num) {
                return;
            }
            last = last->next;
        }
        if(last->num == num) {
            return;
        }
        last->next = temp;
    }
    info->table = chainTable;
}
//resize
PCHAIN *resizeChain(PTABLECHAIN info) {
    int oldSize = info->size;
    int newSize = findNextPrime(oldSize*2);
    PCHAIN *oldTable = info->table;
    int funcHash = 0;
    int num = 0;
    //int i = 0;
    int elementsNum = 0;
    PCHAIN *newTable;

    newTable = malloc(sizeof(CHAIN*)*newSize);
    info->table = newTable;
    info->size = newSize;
    info->elementsNum = 0;

    for(int k = 0; k < newSize; k++) {
        newTable[k] = NULL;
    }

    for (int i = 0; i < oldSize; i++) {
        if(oldTable[i] != NULL) {
            if(oldTable[i]->next == NULL) {
                num = oldTable[i]->num;
                funcHash = num % newSize;
                insertChain(info, num);
            }
            else {
                while(oldTable[i] != NULL) {
                    num = oldTable[i]->num;
                    funcHash = num % newSize;
                    insertChain(info, num);
                    oldTable[i] = oldTable[i]->next;
                }
            }
        }
        else if (oldTable[i] == NULL) {

        }
    }
    return newTable;
}
//searchChain pre hash table
PCHAIN searchChain(PTABLECHAIN info, int num) {
    PCHAIN *temp = info->table;
    int funcHash = num % info->size;
    PCHAIN shift = temp[funcHash];

    while(1) {
        if (shift->num == num) {
            return shift;
        }
        else {
            if(shift->next == NULL) {
                break;
            }
            shift = shift->next;
        }
    }
}

void printChain(PTABLECHAIN info) {
    PCHAIN print;
    for (int i = 0; i < info->size; i++) {
        if(info->table[i] != NULL) {
            print = info->table[i];
            if(info->table[i]->next == NULL) {
                printf("%d", info->table[i]->num);
            }
            else {
                while(print->next != NULL) {
                    printf("%d", print->num);
                    printf("->");
                    print = print->next;
                }
                printf("%d", print->num);
            }
        }
        else {
            printf("NULL");
        }
        printf("\n");
    }
}

void deleteChain(PTABLECHAIN info, int num) {
    int funcHash = num % info->size;
    PCHAIN *temp = info->table;

    if (temp[funcHash] == NULL) {
        return;
    }
    else {
        PCHAIN find = searchChain(info, num);
        if (find->num == num) {
            find->num = 0;
            //info->size--;

        }
    }
}

void freeChain(PTABLECHAIN *table) {
    PCHAIN tmp;
    PCHAIN next;

    for(int i = 0; i < (*table)->size; i++) {
        tmp = (*table)->table[i];
        while(tmp != NULL) {
            next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
    free(*table);
    *table = NULL;
}