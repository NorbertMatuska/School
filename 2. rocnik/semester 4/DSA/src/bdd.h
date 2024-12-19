#ifndef bdd_h
#define bdd_h

// bdd_node struct - single node of BDD
typedef struct bdd_node {
    char *vector_substring;
    struct bdd_node *left;
    struct bdd_node *right;
} BDD_NODE;

// bdd struct - whole BDD
typedef struct bdd {
    int height; // number of levels
    int variables_count;
    char *vector; // vector string
    struct bdd_node *root;
} BDD;

void deallocate_bdd(BDD_NODE *bdd);
char* n_bit_string(int n, int k);
char* generate_random_binary_string(int n, char *vector);
char BDD_use(BDD *bdd, char *vstup);
BDD *BDD_create(char *bfunkcia);
void BDD_create_nodes(BDD *bdd, BDD_NODE *root, char *vector);
BDD_NODE *BDD_create_node(char *vector_substring);
BDD *BDD_init(char *bfunkcia);
int power(int power);
int calculate_variables_count(char *vector);

#endif /* bdd_h */
