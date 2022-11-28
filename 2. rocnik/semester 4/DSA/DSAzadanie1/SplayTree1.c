//
// Created by 42190 on 3/14/2022.
//

#include "SplayTree1.h"
#include <stdio.h>
#include <stdlib.h>


//pomocna funkcia na vytvorenie noveho stromu
PSPLAY newSplay(int num) {
    PSPLAY data = (PSPLAY)malloc(sizeof(SPLAY));

    data->num = num;
    data->right = NULL;
    data->left = NULL;

    return (data);
}

//funkcia na otocenie substromu, podobne ako pri AVL
PSPLAY rightRotateSplay(PSPLAY oldNode) {
    PSPLAY newNode = oldNode->left;
    oldNode->left = newNode->right;
    newNode->right = oldNode;

    return newNode;
}

PSPLAY leftRotateSplay(PSPLAY oldNode) {
    PSPLAY newNode = oldNode->right;
    oldNode->right = newNode->left;
    newNode->left = oldNode;

    return newNode;
}

//tato funkcia prenesie num do korena stromu ak je to mozne
//ak nie, prenesie to posledne "navstiveny" num
//modifikuje strom a vrati novy koren
PSPLAY splay(PSPLAY root, int num) {

    if (root == NULL) {
        return root;
    }

    if (root->num > num) {
        //num nieje v strome, mozeme skoncit
        if (root->left == NULL) {
            return root;
        }

        if (root->left->num > num) {
            root->left->left = splay(root->left->left, num);
            root = rightRotateSplay(root);
        }
        else if (root->left->num < num) {
            root->left->right = splay(root->left->right, num);
            //prva rotacia pre left
            if(root->left->right != NULL) {
                root->left = leftRotateSplay(root->left);
            }
        }
        else if (root->num == num) {
            return root;
        }
        else {
            //druha rotacia pre root pomocou ternarneho operatora
            return (root->left == NULL) ? root : rightRotateSplay(root);
        }
    }
        //num musi byt na pravej strane


    else {
        if (root->right == NULL) {
            return root;
        }

        if (root->right->num > num) {
            root->right->left = splay(root->right->left, num);

            if (root->right->left != NULL) {
                root->right = rightRotateSplay(root->right);
            }
        }
        else if (root->right->num < num) {
            root->right->right = splay(root->right->right, num);
            root = leftRotateSplay(root);

        }

        return (root->right == NULL) ? root : leftRotateSplay(root);
    }
}

//vyhladavacia funkcia
PSPLAY searchSplay(PSPLAY root, int num) {
    //return splay(root, num);

    /*if (root == NULL) {
        return NULL;
    }
    else {
        if (num == root->num) {

            splay(root, num);
        } else if (num < root->num) {
            printf("%d %d\n", root->num, num);
            return searchSplay(root->left, num);
        } else if (num > root->num) {

            return searchSplay(root->right, num);
        } else {

            return NULL;
        }
    }*/
    PSPLAY tmp = root;
    if (root == NULL) {
        return root;
    }
    else if(root->num == num) {
        return root;
    }
    else {
        while(1) {
            if (tmp->num > num) {
                if (tmp->left == NULL) {
                    return root;
                }
                else {
                    tmp = tmp->left;
                }
            }
            else if (tmp->num < num) {
                if (tmp->right == NULL) {
                    return root;
                }
                else {
                    tmp = tmp->right;
                }
            }
            else if (tmp->num == num) {

                return splay(tmp, num);

            }
        }
    }
}

//vkladacia funkcia
PSPLAY insertSplay(PSPLAY root, int num) {
    //ak je strom prazdny
    if (root == NULL) {
        return newSplay(num);
    }
    //prinesie najblizsi "list" ku korenu
    root = splay(root, num);
    //ak je uz num v strome, return
    if (root->num == num) {
        return root;
    }
    else {
        //treba alokovat pamat pre novy num
        PSPLAY newNum = newSplay(num);

        //ak je num korena vacsi, spravime koren ako pravy child newNum
        //a skopirujeme lavy child korena do newNum
        if (root->num > num) {
            newNum->right = root;
            newNum->left = root->left;
            root->left = NULL;
        }
        else {
            newNum->left = root;
            newNum->right = root->right;
            root->right = NULL;
        }

        return newNum; //newNum sa stane novym korenom
    }
}

//funkcia na vymazanie num zo Splay Tree
//vracia novy koren stromu po vymazani num
PSPLAY deleteSplay(PSPLAY root, int num) {
    PSPLAY temp;

    if(root == NULL) {
        return NULL;
    }
    //"splayneme" num ktore nam bolo dane

    root = searchSplay(root, num);

    //ak sa tam nenachadza spravne num, return root
    if (num != root->num) {
        return root;
    }

    if(root->left == NULL) {
        temp = root;
        root = root->right;
    }

    else {

        temp = root;
        //kedze num == root->num, tak po splay(root->left, num) strom kt. dostaneme
        //nebude mat pravych child/potomkov a max splayTr v lavom podstrome bude "splaynuta"
        //novy root
        root = splay(root->left, num);

        //spravime praveho potomka stareho korena ako praveho potomka noveho korena
        root->right = temp->right;
    }

    free(temp);

    //novy koren
    return root;

}

void printSplay(PSPLAY root) {
    if (root != NULL) {
        printf("%d\n", root->num);
        printSplay(root->right);
        printSplay(root->left);
    }
}
