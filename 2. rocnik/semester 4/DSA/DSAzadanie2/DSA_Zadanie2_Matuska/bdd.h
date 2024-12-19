#ifndef DSAZADANIE2_BDD_H
#define DSAZADANIE2_BDD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct bdd_node {
    struct bdd_node *left;
    struct bdd_node *right;
    int lvl;
}BDD_NODE, *PBDD_NODE;

typedef struct bdd {
    int size;
    int variables_count;
    //char *vector;
    PBDD_NODE root;
}BDD, *PBDD;

int power(int power);
//int calculate_variables_count(char *vector);
char *generate_random_binary_string(int n, char *vector);
char *n_bit_string(int n, int k);
void deallocate_bdd(PBDD_NODE bdd);
PBDD BDD_create(char *bfunkcia, int *one, int *zero);
PBDD_NODE build_BDD(PBDD_NODE parent, char *bfunkcia, int lvl, int *size, int *one, int *zero);
PBDD ROBDD_create(char *bfunkcia, int *one, int *zero);
PBDD_NODE *init(char *bfunkcia);
PBDD_NODE build_ROBDD(PBDD_NODE parent, char *bfunkcia, int lvl, PBDD_NODE **hashtable, int *size, int *one, int *zero);
void hashInsert(PBDD_NODE node, PBDD_NODE ** hashtable, int h, int lvl);
int findHashIndex(PBDD_NODE node, PBDD_NODE **hashtable, int lvl, int h_size, int *flag);
int getHash(void* ptr);
char ROBDD_use(PBDD bdd, char *vstupy);
int getResult(PBDD_NODE parent, char *vstupy);

#endif //DSAZADANIE2_BDD_H
