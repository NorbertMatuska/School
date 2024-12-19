#include "tester.h"
#include "bdd.h"

void tester(int test_count, int variable_count) {
    srand((unsigned int) time(NULL));

    clock_t t_use_temp, t_create_temp, t_use_temp_bdd, t_create_temp_bdd;
    double time_taken_create = 0;
    double time_taken_use = 0;
    double time_taken_create_bdd = 0;
    double time_taken_use_bdd = 0;


    int combinations = power(variable_count);
    float percentage = 0;
    char *vector = malloc(combinations*sizeof(char) + 1);
    char *permutation;
    PBDD bdd;
    PBDD robdd;
    int one = 1;
    int zero = 0;


    printf("starting the testing\nvariable count: %d\ntest count: %d\nprogress: ", variable_count, test_count);
    for(int i = 0; i < test_count; i++) {
        if((float)i / (float)test_count > percentage) {
            printf("#");
            percentage += 0.1;
        }
        vector = generate_random_binary_string(combinations, vector);
        t_create_temp = clock();
        robdd = ROBDD_create(vector, &one, &zero);
        t_create_temp = clock() - t_create_temp;
        time_taken_create += ((double)t_create_temp)/CLOCKS_PER_SEC;

        t_create_temp_bdd = clock();
        bdd = BDD_create(vector, &one, &zero);
        t_create_temp_bdd = clock() - t_create_temp_bdd;
        time_taken_create_bdd += ((double)t_create_temp_bdd) / CLOCKS_PER_SEC;

        for(int k = 0; k < combinations; k++) {
            permutation = n_bit_string(k, variable_count);

            t_use_temp = clock();
            ROBDD_use(robdd, permutation);
            t_use_temp = clock() - t_use_temp;
            time_taken_use += ((double)t_use_temp)/CLOCKS_PER_SEC;

            t_use_temp_bdd = clock();
            ROBDD_use(bdd, permutation);
            t_use_temp_bdd = clock() - t_use_temp_bdd;
            time_taken_use_bdd += ((double)t_use_temp_bdd) / CLOCKS_PER_SEC;
            //deallocate_bdd(robdd->root);

            free(permutation);
        }

    }

    printf("\ntesting ended\n");
    printf("ROBDD_create took %f seconds, on average 1 ROBDD_create function call took %f seconds.\n", time_taken_create, time_taken_create/test_count);
    printf("BDD_use took %f seconds, on average 1 BDD_use function call took %f seconds for ROBDD.\n", time_taken_use, time_taken_use/test_count);
    printf("-\n");
    printf("BDD_create took %f seconds, on average 1 BDD_create function call took %f seconds.\n", time_taken_create_bdd, time_taken_create_bdd/test_count);
    printf("BDD_use took %f seconds, on average 1 BDD_use function call took %f seconds for BDD.\n", time_taken_use_bdd, time_taken_use_bdd/test_count);
    printf("-\n\n");

    overallTesting(robdd, bdd, vector);

    free(vector);
}

void overallTesting(PBDD robdd, PBDD bdd, char *vector) {
    //double time_reduced = 0, time_basic = 0;
    //int test_count = 1;

    printf("ROBDD number of nodes: %d\n", robdd->size);
    printf("BDD number of nodes: %d\n", bdd->size);
    printf("Reduced percentage: %.2f%%\n\n", 100-(float)robdd->size / bdd->size * 100);

    test_results(robdd, bdd, vector);
    /*
    for (int i = 0; i < test_count; i++) {
        time_reduced += testDecidingTime(robdd, vector);
        time_basic += testDecidingTime(bdd, vector);
    }
    printf("ROBDD average deciding time: %f seconds\n", time_reduced / test_count);
    printf("BDD average deciding time: %f seconds\n", time_basic / test_count);*/
}

void test_results(PBDD robdd, PBDD bdd, char *vector) {
    int i, log = log2(strlen(vector));
    char *key = malloc(sizeof(char) * log);

    for (i = 0; i < log; i++) {
        key[i] = '0';
    }
    key[i] = '\0';
    for (i = 0; i < power(log); i++) {
        //strcpy(key, increaseBinaryString(key));
        if (ROBDD_use(robdd, key) != ROBDD_use(bdd, key)) {
            printf("ERROR %s ROBDD: %d - BDD: %d\n", key, ROBDD_use(robdd, key), ROBDD_use(bdd, key));
        }

    }
}

char *increaseBinaryString(char *string) {
    int len = strlen(string);
    char *buff = malloc(sizeof(char) * len);
    strcpy(buff, string);

    for (int i = len - 1; i >= 0; i--) {
        if(buff[i] == '0') {
            buff[i] = '1';
            return buff;
        }
        buff[i] = '0';
    }
    return buff;
}

double testDecidingTime(PBDD bdd, char *vector) {
    int i, log = log2(strlen(vector));
    char *key = malloc(sizeof(char) * log);

    for (i = 0; i < log; i++) {
        key[i] = '0';
    }
    key[i] = '\0';

    clock_t dt = 0, past;
    for (i = 0; i < power(log); i++) {
        strcpy(key, increaseBinaryString(key));

        past = clock();
        ROBDD_use(bdd, vector);
        dt += clock() - past;
    }

    return dt / CLOCKS_PER_SEC;
}