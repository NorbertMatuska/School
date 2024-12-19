//
// Created by 42190 on 3/14/2022.
//

#ifndef DSAZADANIE1_SPLAYTREE1_H
#define DSAZADANIE1_SPLAYTREE1_H
#include <stdio.h>
#include <stdlib.h>

typedef struct splayTree {
    int num;
    struct splayTree *right;
    struct splayTree *left;
} SPLAY, *PSPLAY;

PSPLAY newSplay(int num);

PSPLAY rightRotateSplay(PSPLAY oldNode);

PSPLAY leftRotateSplay(PSPLAY oldNode);

PSPLAY splay(PSPLAY root, int num);

PSPLAY searchSplay(PSPLAY root, int num);

PSPLAY insertSplay(PSPLAY root, int num);

PSPLAY deleteSplay(PSPLAY root, int num);

void printSplay(PSPLAY root);

#endif //DSAZADANIE1_SPLAYTREE1_H
