#include "bdd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int calculate_variables_count(char *vector)
{
    int vector_length = (int) strlen(vector), var_amount = 0;
    
    // calculate variable amount by finding 2 to the power of X equals vector length,
    // where X is variable amount
    for (int i = 2; i <= vector_length; i *= 2)
        var_amount++;
    
    return var_amount;
}

int power(int power)
{
    int result = 1;
    
    for (int i = 1; i <= power; i++)
        result *= 2;
    
    return result;
}

BDD *BDD_init(char *bfunkcia)
{
    BDD *bdd = malloc(sizeof(BDD));
    
    bdd->variables_count = calculate_variables_count(bfunkcia);
    
    bdd->vector = malloc(sizeof(char)*strlen(bfunkcia)+1);
    strcpy(bdd->vector, bfunkcia);
        bdd->vector[strlen(bfunkcia)+1] = '\0';
    
    bdd->height = bdd->variables_count + 1;
    
    bdd->root = NULL;
    
    return bdd;
}

BDD_NODE *BDD_create_node(char *vector_substring)
{
    
    // allocate 1 bdd node
    BDD_NODE *bdd_node = malloc(sizeof(BDD_NODE));
    
    // allocate memory for vector of the node
    bdd_node->vector_substring = malloc(sizeof(char)*strlen(vector_substring)+1);
    
    // copy the function parameter vector string to bdd node struct
    strcpy(bdd_node->vector_substring, vector_substring);
    
    return bdd_node;
}

// recursively create BDD nodes
void BDD_create_nodes(BDD *bdd, BDD_NODE *root, char *vector)
{
    
    // last level, exit the recursion
    if (strlen(vector) < 2) {
        root->left = NULL;
        root->right = NULL;
        return;
    }
    
    // calculate length of vector and length of new vector substring
    int vector_length = (int) strlen(vector), vector_length_substring = vector_length / 2;
    
    // left children node
    char *vector_left = malloc(vector_length_substring+1); // plus one for the null character
    memcpy(vector_left, vector, vector_length_substring); // copy the first half of the vector
    vector_left[vector_length_substring] = '\0'; // null character
    root->left = BDD_create_node(vector_left); // create the BDD node
    BDD_create_nodes(bdd, root->left, vector_left); // insert the node to the left side of BDD
    free(vector_left); // free the temporary vector left substring
    
    // right side
    char *vector_right = malloc(vector_length_substring+1); // one for the null terminator
    memcpy(vector_right, vector+vector_length_substring, vector_length_substring); // copy the second half of the vector
    vector_right[vector_length_substring] = '\0'; // null character
    root->right = BDD_create_node(vector_right); // create the BDD node
    BDD_create_nodes(bdd, root->right, vector_right); // insert the node to the right side of BDD
    free(vector_right); // free the temporary vector right substring
}

BDD *BDD_create(char *bfunkcia)
{
    
    // BDD init and create root node
    BDD *bdd = BDD_init(bfunkcia);
    bdd->root = malloc(sizeof(BDD_NODE));
    bdd->root = BDD_create_node(bfunkcia);
    
    // create the whole BDD
    BDD_create_nodes(bdd, bdd->root, bfunkcia);
    
    return bdd;
}

char BDD_use(BDD *bdd, char *vstup)
{
    BDD_NODE *temp = bdd->root;
    
    for (int x = 0, i = 1; i < bdd->height; i++, x++) {
        // go to right child
        if (vstup[x] == '1')
            temp = temp->right;
        // go to left child
        else if (vstup[x] == '0')
            temp = temp->left;
        else
            return -1;
    }
    
    return *temp->vector_substring;
}

char* generate_random_binary_string(int n, char *vector)
{
    for (int i = 0; i < n; i++)
        vector[i] = ((int)rand() % 2) ? '1' : '0';
    
    vector[n] = '\0';
 
    return vector;
}

char* n_bit_string(int n, int k)
{
    // allocate string
    char *vector = malloc(k * sizeof(char) + 1);
    
    // set all chars to 0
    memset(vector, '0', k);
    int i = 1;
    
    // generate the nbit string by dividing the number
    while (n > 0) {
        vector[k-i] = (!(n % 2)) ? '0' : '1';
        n = n / 2;
        i++;
    }
    vector[k] = '\0';
    return vector;
}

void deallocate_bdd(BDD_NODE *bdd)
{
    if (bdd == NULL)
        return;
    
    // recursive depth search
    deallocate_bdd((*bdd).left);
    deallocate_bdd((*bdd).right);
    
    // deallocation of BDD node
    free(bdd->vector_substring);
    free(bdd);
}
