#include "tester.h"
#include "bdd.h"

void tester(int test_count, int variable_count)
{

    srand((unsigned int)time(NULL));
    
    clock_t t_use_temp, t_create_temp;
    double time_taken_create = 0, time_taken_use = 0;
    
    // calculate the combinations
    int combinations = power(variable_count);
    float percentage = 0;
    char *vector = malloc(combinations * sizeof(char) + 1);
    char *permutation;
    BDD *bdd;
    
    printf("STARTING TESTS\nVariable count: %d\nTest count: %d\nProgress: ", variable_count, test_count);
    for (int i = 0; i < test_count; i++) {
        
        // "progress bar"
        if ((float)i / (float)test_count > percentage) {
            printf("#");
            percentage += 0.1;
        }
        
        // generate vector & bdd
        vector = generate_random_binary_string(combinations, vector);
        t_create_temp = clock();
        bdd = BDD_create(vector);
        t_create_temp = clock() - t_create_temp;
        time_taken_create += ((double)t_create_temp)/CLOCKS_PER_SEC;
        
        // try all the combinations
        for (int i = 0; i < combinations; i++) {
            // generate permutation based on iteration
            permutation = n_bit_string(i, variable_count);
            
            // check if BDD is implemented properly
            t_use_temp = clock();
            if (BDD_use(bdd, permutation) != vector[i])
                printf("ERROR! should be %c\n", vector[i]);
            t_use_temp = clock() - t_use_temp;
            time_taken_use += ((double)t_use_temp)/CLOCKS_PER_SEC;
            
            free(permutation);
        }
        
        // freeing memory for next iteration
        deallocate_bdd(bdd->root);
        free(bdd->vector);
        free(bdd);
    }
    
    free(vector);
    
    printf("\nTESTS COMPLETED!\n");

    printf("BDD create took %f seconds, on average 1 BDD create function call took %f seconds.\n", time_taken_create, time_taken_create/test_count);
    printf("BDD use took %f seconds, on average 1 BDD create function call took %f seconds.\n", time_taken_use, time_taken_use/test_count);
}
