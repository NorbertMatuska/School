#include "tester.h"

int main() {

    int test_count = 0;
    int variable_count = 0;

    printf("Number of tests:\n");
    while(scanf(" %d", &test_count) == 1) {
        printf("Number of variables:\n");

        while(scanf(" %d", &variable_count) == 1) {
            tester(test_count, variable_count);
            break;
        }
        printf("\n\nNumber of tests:\n");
    }

    return 0;
}
