#include "bdd.h"

int power(int power) {
    int result = 1;

    for (int i = 1; i <= power; i++) {
        result *= 2;
    }
    return result;
}
/*
 * nepotrebne
int calculate_variables_count(char *vector) {
    int vector_length = (int) strlen(vector), var_amount = 0;

    for (int i = 2; i <= vector_length; i *= 2) {
        var_amount++;
    }
    return var_amount;
}
*/

char To_Vector(char *bfunkcia, char *poradie, char *hodnoty){
    int tmpvalue = 1;
    int value = 2;
    int i,x;
    int negate = 0;
    char *string = (char *)malloc((strlen(bfunkcia)+1)*sizeof(char));
    for(i = 0;i<strlen(bfunkcia);i++){
        string[i] = bfunkcia[i];
    }
    char * token = strtok(string, "+");
    while( token != NULL ) {
        tmpvalue = 1;
        for(i =0;i<strlen(token);i++) {
            if(token[i]!='!'){
                for(x = 0;x<strlen(poradie);x++){
                    int tmp;
                    if(poradie[x]==token[i]){
                        tmp = hodnoty[x]-48;
                        if(negate==1){
                            if(tmp==0)tmp=1;
                            else if(tmp==1)tmp=0;
                            negate = 0;
                        }
                        tmpvalue = tmpvalue*tmp;
                    }
                }
            }else{
                negate=1;
            }
        }
        if(tmpvalue==1){
            value=1;
        }
        token = strtok(NULL, "+");
    }
    if(value==2){
        value=0;
    }
    return value+48;
}

char *returnVector() {
    char * bfunkcia = "ABCDE";
    char * poradie = "ABCDE";
    int variables_count = strlen(poradie);
    int dlzka = pow(2, variables_count);
    //printf("%d\n",dlzka);
    int tmp, pisem, interval, x, i, j, z;
    char *matica[variables_count];
    char *vector = (char *)malloc((dlzka+1)*sizeof(char));
    for (i = 0; i < variables_count; i++) {
        matica[i] = (char *) malloc(dlzka * sizeof(int));
    }
    //printf("Formula %s\nPoradie: %s\n",bfunkcia,poradie);
    //printf("dlzka: %d variables_count: %d\n", dlzka, variables_count);
    for (x = 0; x < variables_count; x++) {
        tmp = 0;
        pisem = 0;

        for (z = 0; z < dlzka; z++) {
            tmp += 1;
            interval = pow(2,(variables_count - 1 - x));
            matica[x][z] = pisem;
            if (pisem == 0 && interval == tmp) {
                tmp = 0;
                pisem = 1;
            }
            else if (pisem == 1  && interval == tmp) {
                tmp = 0;
                pisem = 0;
            }
        }
    }
    for(i = 0;i<dlzka;i++){
        char *string = (char *)malloc((variables_count+1)*sizeof(char));
        for(j = 0;j<variables_count;j++){
            string[j] = matica[j][i]+48;
        }
        vector[i] = To_Vector(bfunkcia,poradie,string);
    }
    for(i = 0;i< strlen(vector);i++){
        if(i>=dlzka){
            vector[i] = 0;
        }
    }
    //printf("Vector: %s %d\n",vector, strlen(vector));
    return vector;
}

PBDD_NODE *init(char *bfunkcia) {
    int p, log = log2(strlen(bfunkcia));
    PBDD_NODE *hashtable = malloc(sizeof(PBDD_NODE)*log);

    for(int i = 0; i < log; i++) {
        p = power(i);
        hashtable[i] = malloc(sizeof(BDD_NODE)*p);
        for(int o = 0; o < p; o++) {
            hashtable[i][o].lvl = -1;
        }
    }
    return hashtable;
}

PBDD BDD_create(char *bfunkcia, int *one, int *zero) {
    int size = 2;

    //bfunkcia = returnVector();

    PBDD_NODE node = malloc(sizeof(BDD_NODE));
    PBDD bdd = malloc(sizeof(BDD));

    node = build_BDD(node, bfunkcia, 0, &size, one, zero);
    bdd->root = node;
    bdd->size = size;
    bdd->variables_count = log2(strlen(bfunkcia));

    return bdd;
}

PBDD_NODE build_BDD(PBDD_NODE parent, char *bfunkcia, int lvl, int *size, int *one, int *zero) {
    parent->lvl = lvl;
    PBDD_NODE child1 = malloc(sizeof(BDD_NODE));
    PBDD_NODE child2 = malloc(sizeof(BDD_NODE));

    if (strlen(bfunkcia) > 2) {

        char *s1 = malloc(sizeof(char) * strlen(bfunkcia));
        char *s2 = malloc(sizeof(char) * strlen(bfunkcia));
        //rozdelenie vektora na 2 casti
        strncpy(s1, bfunkcia, strlen(bfunkcia) / 2);
        s1[strlen(bfunkcia) / 2] = '\0';
        strncpy(s2, bfunkcia + strlen(bfunkcia) / 2, strlen(bfunkcia) - strlen(bfunkcia) / 2);
        s2[strlen(bfunkcia) / 2] = '\0';

        parent->left = build_BDD(child1, s1, lvl + 1, size, one, zero);
        parent->right = build_BDD(child2, s2, lvl + 1, size, one, zero);

        (*size) += 1;
        return parent;
    }
    else {
        PBDD_NODE child = malloc(sizeof(BDD_NODE));
        child->lvl = lvl;
        //posledna uroven
        //[0] na lavo cize false
        if (bfunkcia[0] == '0') {
            child->left = zero;
        }
        else {
            child->left = one;
        }
        //[1] je na pravo cize true
        if (bfunkcia[1] == '0') {
            child->right = zero;
        }
        else {
            child->right = one;
        }

        (*size) += 3;

        return child;
    }
}

PBDD ROBDD_create(char *bfunkcia, int *one, int *zero) {
    int size = 2;

    //bfunkcia = returnVector();

    PBDD_NODE *hashtable = init(bfunkcia);
    PBDD_NODE node = malloc(sizeof(BDD_NODE));
    PBDD bdd = malloc(sizeof(BDD));

    build_ROBDD(node, bfunkcia, 0, &hashtable, &size, one, zero);
    bdd->root = hashtable[0];
    bdd->size = size;
    bdd->variables_count = log2(strlen(bfunkcia));

    return bdd;
}

PBDD_NODE build_ROBDD(PBDD_NODE parent, char *bfunkcia, int lvl, PBDD_NODE **hashtable, int *size, int *one, int *zero) {
    int h, h_size = power(lvl), flag;
    parent->lvl = lvl;

    if(strlen(bfunkcia) > 2) {
        PBDD_NODE child1 = malloc(sizeof(BDD_NODE));
        PBDD_NODE child2 = malloc(sizeof(BDD_NODE));

        char *s1 = malloc(sizeof(char) * strlen(bfunkcia));
        char *s2 = malloc(sizeof(char) * strlen(bfunkcia));
        //rozdelenie vektora na 2 casti
        strncpy(s1, bfunkcia, strlen(bfunkcia)/2);
        s1[strlen(bfunkcia)/2] = '\0';
        strncpy(s2, bfunkcia + strlen(bfunkcia) / 2, strlen(bfunkcia) - strlen(bfunkcia) / 2);
        s2[strlen(bfunkcia) / 2] = '\0';

        //vytvorenie rootov a do kazdeho posleme jednu polovicu z vektora
        parent->left = build_ROBDD(child1, s1, lvl + 1, hashtable, size, one, zero);
        parent->right = build_ROBDD(child2, s2, lvl + 1, hashtable, size, one, zero);
        //redukcia typu S - korene su ten isty uzol
        if (parent->right == parent->left) {
            //ak je to uplne prvy pointer, tak tam musime nieco vlozit, aby to nebolo prazdne aj ked je to redukovane na 0
            if(lvl == 0){
                hashInsert(parent, hashtable,0, lvl);
            }
            return parent->right;
        }
        else {
            //redukcia typu I - if uz rovnaky uzol existuje
            flag = 1;
            h = findHashIndex(parent, hashtable, lvl, h_size, &flag);
            //takyto prvok v zozname nie je
            if(h != -1) {
                hashInsert(parent, hashtable, h, lvl);
                (*size) += 1;
                return &(*hashtable)[lvl][h];
            }
            return &(*hashtable)[lvl][flag];
        }
    }
    else {
        //vytvorenie a redukovanie prvkov na poslednej urovni == lvl
        PBDD_NODE child = malloc(sizeof(BDD_NODE));
        child->lvl = lvl;

        //[0] je na lavo cize false
        if(bfunkcia[0] == '0') {
            child->left = zero;
        }
        else {
            child->left = one;
        }
        //[1] je napravo cize true
        if(bfunkcia[1] == '0') {
            child->right = zero;
        }
        else {
            child->right = one;
        }

        if (child->right == child->left) {
            return child->right;
        }
        flag = 1;
        h = findHashIndex(child, hashtable, lvl, h_size, &flag);
        //takyto prvok v zozname nieje
        if (h != -1) {
            hashInsert(child, hashtable, h, lvl);
            (*size) += 1;
            return &(*hashtable)[lvl][h];
        }
        return &(*hashtable)[lvl][flag];
    }
}

//vlozi do hashtable
void hashInsert(PBDD_NODE node, PBDD_NODE **hashtable, int h, int lvl) {
    (*hashtable)[lvl][h].right = node->right;
    (*hashtable)[lvl][h].left = node->left;
    (*hashtable)[lvl][h].lvl = node->lvl;
}

int findHashIndex(PBDD_NODE node, PBDD_NODE **hashtable, int lvl, int h_size, int *flag) {
    //ziska hash index podla pointera right a left root
    int h = (getHash(node->left) >> 1 + getHash(node->right)) % h_size;
    if(h == -1) {
        printf("NULL pointer in hash\n");
        return -2;
    }
    //zistujeme zhodu a ak ano, zistujeme ci je to rovnaky uzol
    while((*hashtable)[lvl][h].lvl != -1) {
        if ((*hashtable)[lvl][h].left == node->left && (*hashtable)[lvl][h].right == node->right) {
            *flag = h;
            return -1;
        }
        h = (h + 1) % h_size;
    }
    return h;
}
//vrati hash z pointra
int getHash(void* ptr) {
    if (ptr != NULL) {

        int value = (int)ptr;
        value = ~value + (value << 11);
        value = value ^ (value >> 7);
        value = value + (value << 2);
        value = value ^ (value >> 5);
        value = value * 33;
        value = value ^ (value >> 17);
        return value;
    }
    return -1;
}
//vrati vyslednu hodnotu z rovnice podla kluca(vstupy)
int getResult(PBDD_NODE parent, char *vstupy) {
    int *x = parent;
    //ak je na konci (v 0 alebo v 1), konci
    if (*x == 1 || *x == 0) {
        return *x;
    }

    //inak sa posuvame do podkorenov
    if (vstupy[parent->lvl] == '1') {
        x = parent->right;
    }
    else {
        x = parent->left;
    }

    return getResult(x, vstupy);
}

char ROBDD_use(PBDD bdd, char *vstupy) {
    return getResult(bdd->root, vstupy);
}

char *generate_random_binary_string(int n, char *vector) {
    for (int i = 0; i < n; i++) {
        vector[i] = ((int)rand() % 2) ? '1' : '0';
    }
    vector[n] = '\0';

    return vector;
}

char *n_bit_string(int n, int k) {
    char *vector = malloc(k * sizeof(char)+1);

    memset(vector, '0', k);
    int i = 1;

    while(n > 0) {
        vector[k-i] = (!(n % 2)) ? '0' : '1';
        n = n / 2;
        i++;
    }
    vector[k] = '\0';
    return vector;
}

void deallocate_bdd(PBDD_NODE bdd) {
    if (bdd == NULL) {
        return;
    }

    deallocate_bdd((*bdd).left);
    deallocate_bdd((*bdd).right);

    //free(bdd->vector_substring);
    free(bdd);
}