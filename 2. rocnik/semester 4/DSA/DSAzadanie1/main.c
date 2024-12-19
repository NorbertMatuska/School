#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SplayTree1.h"
#include "ChainHash.h"
#include "LinearHash.h"

#define INITTIME clock_t start_t, end_t, total_t
#define START start_t = clock()
#define STOP end_t = clock()

//struct na vytvorenie stromu
typedef struct avltree {
    int num;
    struct avltree* right;
    struct avltree* left;
    int height;
}AVLTREE, * PAVLTREE;

//pomocou tohto si vytvaram zaciatok noveho stromu
PAVLTREE newTree(int numb) {
    PAVLTREE data = (PAVLTREE)malloc(sizeof(AVLTREE));

    data->num = numb;
    data->right = NULL;
    data->left = NULL;
    data->height = 1;

    return (data);
}

void freeTree(PAVLTREE data) {
    if(data == NULL) {
        return;
    }
    freeTree(data->right);
    freeTree(data->left);
    free(data);
    data = NULL;
}
//vypocitanie vysky stromu
int calcHeight(PAVLTREE N) {
    if (N == NULL) {
        return 0;
    }
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b; //ternarny operator
}

PAVLTREE rightRotation(PAVLTREE oldRoot) {
    PAVLTREE newRoot = oldRoot->left;
    PAVLTREE t = newRoot->right;
    newRoot->right = oldRoot;
    oldRoot->left = t;

    oldRoot->height = max(calcHeight(oldRoot->left), calcHeight(oldRoot->right) + 1);
    newRoot->height = max(calcHeight(newRoot->left), calcHeight(newRoot->right) + 1);

    return newRoot;
}

PAVLTREE leftRotation(PAVLTREE oldRoot) {
    PAVLTREE newRoot = oldRoot->right;
    PAVLTREE t = newRoot->left;
    newRoot->left = oldRoot;
    oldRoot->right = t;

    oldRoot->height = max(calcHeight(oldRoot->left), calcHeight(oldRoot->right) + 1);
    newRoot->height = max(calcHeight(newRoot->left), calcHeight(newRoot->right) + 1);

    return newRoot;
}

int findBalance(PAVLTREE N) {
    if (N == NULL) {
        return 0;
    }
    return calcHeight(N->left) - calcHeight(N->right);
}

PAVLTREE insert(PAVLTREE node, int num) {
    //treba nam najst spravnu poziciu na inser a tam to vlozit
    if (node == NULL) {
        return (newTree(num));
    }
    if (num < node->num) {
        node->left = insert(node->left, num);
    }
    else if (num > node->num) {
        node->right = insert(node->right, num);
    }
    else {
        return node;
    }
    //treba "aktualizovat" vyvazovaci faktor pre kazdu node a vyvazovat strom
    node->height = 1 + max(calcHeight(node->left), calcHeight(node->right));

    int balance = findBalance(node);

    if (balance > 1 && num < node->left->num) {
        return rightRotation(node);
    }
    if (balance < -1 && num > node->right->num) {
        return leftRotation(node);
    }
    if (balance > 1 && num > node->left->num) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    if (balance < -1 && num < node->right->num) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}
PAVLTREE minimalValNode(PAVLTREE node) {
    PAVLTREE curr = node;

    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}
//funkcia na vymazanie splayTr
PAVLTREE delete(PAVLTREE root, int num) {
    //musime najst a vymazat splayTr
    if (root == NULL) {
        return root;
    }
    if (num < root->num) {
        root->left = delete(root->left, num);
    }
    else if (num > root->num) {
        root->right = delete(root->right, num);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            PAVLTREE temp = root->left ? root->left : root->right; //ternarny operator

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            PAVLTREE temp = minimalValNode(root->right);
            root->num = temp->num;
            root->right = delete(root->right, temp->num);
        }
    }
    if (root == NULL) {
        return root;
    }

    //Musime vyvazovat strom
    root->height = 1 + max(calcHeight(root->left), calcHeight(root->right));

    int balance = findBalance(root);
    if (balance > 1 && findBalance(root->left) >= 0) {
        return rightRotation(root);
    }
    if (balance > 1 && findBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if (balance < -1 && findBalance(root->right) <= 0) {
        return leftRotation(root);
    }
    if (balance < -1 && findBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}
//vypis strom
void printTree(PAVLTREE root) {
    if(root != NULL) {
        printf("%d\n", root->num);
        printTree(root->left);
        printTree(root->right);
    }
}
PAVLTREE searchAVL(PAVLTREE node, int num) {
    if (node == NULL) {
        return NULL;
    }
    else {
        if (num < node->num) {
            return searchAVL(node->left, num);
        } else if (num > node->num) {
            return searchAVL(node->right, num);
        } else {
            return node;
        }
    }
}
//################################################################################################################

void insertToAVL(int *arr) {
    PAVLTREE ret = NULL;
    PAVLTREE root = NULL;
    INITTIME;

    START;
    for(int i = 0; i < 10000000; i++) {
        root = insert(root, arr[i]);
    }
    STOP;
    printf("cas insertu do AVL je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    START;
    for (int i = 0; i < 10000000; i++) {
        ret = searchAVL(root, arr[i]);
        //printf("%d\n", ret->num);
    }
    STOP;
    printf("cas prehladavania AVL je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    START;
    for(int i = 0; i < 10000000; i++) {
        root = delete(root, arr[i]);
    }
    STOP;
    printf("cas deletu AVL je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);
    printf("\n");


    freeTree(root);
}

void insertToSplay(int *arr) {
    PSPLAY root = NULL;
    PSPLAY ret = NULL;
    INITTIME;

    START;
    for (int i = 0; i < 10000000; i++) {
        root = insertSplay(root, arr[i]);
        //printf("%d\n", root->num);
    }
    STOP;
    printf("cas insertu do Splay je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);
    //printSplay(root);
    START;
    for(int i = 10000000; i > 0; i--) {
        root = searchSplay(root, arr[i]);
    }
    STOP;
    printf("cas prehladavania Splay je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);
    START;
    for(int i = 0; i < 10000000; i++) {
        //printf("%d %d\n", root->num, arr[i]);
        root = deleteSplay(root, arr[i]);

    }
    STOP;
    printf("cas deletu Splay je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    printf("\n");
}

void insertToChain(int *arr) {
    PTABLECHAIN info = (TABLECHAIN*) malloc(sizeof(TABLECHAIN));
    info->size = 13;
    info->elementsNum = 0;
    INITTIME;

    double findResize;
    PCHAIN *chainTable;
    PCHAIN ret;

    chainTable = malloc(sizeof(CHAIN) * info->size);
    for (int i = 0; i < info->size; i++) {
        chainTable[i] = NULL;
    }
    info->table = chainTable;

    START;
    for (int i = 0; i < 10000000; i++) {
        insertChain(info, arr[i]);
        findResize = (double) info->elementsNum / info->size;
        if (findResize >= 1.5) {
            chainTable = resizeChain(info);
        }
    }
    STOP;
    printf("cas insertu do Chain Hash je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    START;
    for(int i = 0; i < 10000000; i++) {
        ret = searchChain(info, arr[i]);
    }
    STOP;
    printf("cas prehladavania Chain Hash je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    for(int i = 0; i < 10000000; i++) {
        deleteChain(info, arr[i]);
    }
    printf("cas deletu Chain Hash je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);
    printf("\n");

    freeChain(&info);
}

void insertToLinear(int *arr) {
    INITTIME;

    PLINEAR ret;

    linArr = (PLINEAR*) malloc(hashSize * sizeof(LINEAR));
    begin();

    START;
    for(int i = 0; i < 10000000; i++) {
        insertLinear(arr[i], 1);
    }
    STOP;
    printf("cas insertu do Linear Hash je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);

    START;
    for (int i = 0; i < 10000000; i++) {
        ret = searchLinear(arr[i]);
    }
    STOP;
    printf("cas prehladania Linear Hash je: %10f\n", (double)(-start_t + end_t)/CLOCKS_PER_SEC);
    printf("\n");
    //sizeLin = 17;
}

int main() {
    PAVLTREE root = NULL;
    PSPLAY rootSplay = NULL;
    int x = 0;
    int *arr = malloc(10000000*sizeof(int));
    for (int i = 0; i < 10000000; i++) {
        arr[i] = i;
    }
    printf("Test 0 az 10 milionov\n");
    insertToAVL(arr);
    insertToSplay(arr);
    insertToChain(arr);
    //insertToLinear(arr);

    free(arr);
    printf("Test 10 milionov az 0\n");
    int *pole = malloc(10000000 * sizeof(int));
    for (int i = 10000000,j=0; i > 0; i--,j++)
    {
        pole[j] = i;
    }
    insertToAVL(pole);
    insertToSplay(pole);
    insertToChain(pole);
    insertToLinear(pole);

    free(pole);
    return 0;
}
