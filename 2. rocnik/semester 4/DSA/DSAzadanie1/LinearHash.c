//
// Created by 42190 on 3/19/2022.
//

#include "LinearHash.h"
int sizeLin = hashSize;

int linearCode(int key) {
    return key % sizeLin;
}

void begin() {
    for (int i = 0; i < sizeLin; i++) {
        linArr[i] = NULL;
    }
}

PLINEAR searchLinear(int key) {

    int linearIndex = linearCode(key);

    while (linArr[linearIndex] != NULL ) {
        if (linArr[linearIndex]->key == key) {
            return linArr[linearIndex];
        }
        //posuvame sa dalej
        linearIndex++;

        linearIndex %= sizeLin;
    }
    return NULL;
}

void rehash() {
    int oldSize = sizeLin;
    sizeLin *= 2;

    PLINEAR *newArr = (PLINEAR*) malloc(sizeLin*sizeof(PLINEAR));
    PLINEAR *oldArr = linArr;
    linArr = newArr;

    begin();
    numOfLin = 0;
    for (int i = 0; i < oldSize; i++) {
        if(oldArr[i] != NULL) {
            insertLinear(oldArr[i]->key, oldArr[i]->num);
        }
    }
}

void insertLinear(int key, int num) {
    item = (PLINEAR) malloc(sizeof(LINEAR));
    item->key = key;
    item->num = num;

    //zobereme nasu hash
    int linearIndex = linearCode(key);

    //posuvame sa po poli kym nenajdeme prazdnu alebo vymazanu cast
    while(linArr[linearIndex] != NULL) {
        if(linArr[linearIndex]->key == key){
            return;
        }
        //posuvame sa dalej
        linearIndex++;

        linearIndex %= sizeLin;
    }
    linArr[linearIndex] = item;
    numOfLin++;

    if(linearLoad(numOfLin, sizeLin)) {
        rehash();
    }
}

void printLinear() {

    for(int i = 0; i < sizeLin; i++) {
        if(linArr[i] != NULL) {
            printf("(%d,%d)", linArr[i]->key,linArr[i]->num);
        }
        else {
            printf(" -- ");
        }
    }
    printf("\n");
}