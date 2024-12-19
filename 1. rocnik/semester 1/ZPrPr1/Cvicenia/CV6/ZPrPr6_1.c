#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int parne(int* x, int xcount) {
	int* y = (int*)malloc(xcount * sizeof(int));
	int k = 0;
	for (int i = 0; i < xcount; i++) {

		if ((x[i] % 2) == 0) {
			y[k] = x[i];
			k++;
		}
	}
	printf("pocet y: %d \n", k);
	printf("y: {");
	for (int p = 0; p < k; p++) {
		printf("%d,", y[p]);
	}
	printf("}");
	return k;
}

int main()
{
	int* x, size, pocty, con = 0;

	scanf_s("%d", &size);
	x = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		scanf_s("%d", x + i);
		con++;
	}
	pocty = parne(x, con);

	return 0;
}
