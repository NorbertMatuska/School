#ifndef DSAZADANIE2_TESTER_H
#define DSAZADANIE2_TESTER_H

#include <stdio.h>
#include "bdd.h"
void tester(int test_count, int variable_count);
void overallTesting(PBDD robdd, PBDD bdd, char *vector);
void test_results(PBDD robdd, PBDD bdd, char *vector);
char *increaseBinaryString(char *string);
double testDecidingTime(PBDD bdd, char *vector);


#endif //DSAZADANIE2_TESTER_H
