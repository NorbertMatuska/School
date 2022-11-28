//
// Created by 42190 on 3/19/2022.
//

#ifndef DSAZADANIE1_CHAINHASH_H
#define DSAZADANIE1_CHAINHASH_H

#include <stdlib.h>
#include <stdio.h>
typedef struct chain {
    int num;
    struct chain *next;
} CHAIN, *PCHAIN;

typedef struct tableChain {
    PCHAIN *table;
    int size;
    int elementsNum;
} TABLECHAIN, *PTABLECHAIN;

int findPrime(int x);

int findNextPrime(int x);

void insertChain(PTABLECHAIN info, int num);

PCHAIN *resizeChain(PTABLECHAIN info);

PCHAIN searchChain(PTABLECHAIN info, int num);

void printChain(PTABLECHAIN info);

void deleteChain(PTABLECHAIN info, int num);

void freeChain(PTABLECHAIN *table);

#endif //DSAZADANIE1_CHAINHASH_H
