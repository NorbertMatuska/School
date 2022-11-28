#include <stdio.h>
#include "tester.h"

int main(int argc, const char * argv[]) {
    
    int test_count = 0, variable_count = 0;
    
    printf("Number of tests: ");
    while (scanf("%d", &test_count) == 1) {
        printf("Number of variables: ");
        
        while (scanf("%d", &variable_count) == 1) {
            tester(test_count, variable_count);
            break;
        }
        
        printf("\n\nNumber of tests: ");
    }
    
    return 0;
}
