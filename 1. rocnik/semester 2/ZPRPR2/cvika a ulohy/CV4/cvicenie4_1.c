#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {

	int a = 9;
	int b = 35;
	int* p_a = &a;
	int* p_b = &b;

	*p_a = &a;
	*p_b = &b;

	printf("PRED\na = %d\nb = %d\n", a, b);

	vymen_ukazovatele(&p_a, &p_b);

	return 0;
}

int vymen_ukazovatele(int **a, int **b) {

	//printf("%d %d\n", **a, **b);

	int temp = 0;
	temp = **a;
	**a = **b;
	**b = temp;

	printf("PO\na = %d\nb = %d", **a, **b);


	return 0;
}