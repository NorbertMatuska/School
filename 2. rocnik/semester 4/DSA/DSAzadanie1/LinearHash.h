//
// Created by 42190 on 3/19/2022.
//

#ifndef DSAZADANIE1_LINEARHASH_H
#define DSAZADANIE1_LINEARHASH_H
#include <stdlib.h>
#include <stdio.h>

#define linearLoad(N, M) (((double)(N) / (M) >=0.75) ? 1 : 0)
#define hashSize 17

typedef struct linear {
    int num;
    int key;
}LINEAR, *PLINEAR;

PLINEAR *linArr;
PLINEAR item;

int sizeLin;
int numOfLin;

int linearCode(int key);

void begin();

PLINEAR searchLinear(int key);

void rehash();

void insertLinear(int key, int num);

void printLinear();
#endif //DSAZADANIE1_LINEARHASH_H
