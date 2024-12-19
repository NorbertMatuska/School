//STU FIIT
//Norbert Matuška
//6/12/2020
//cvicenie 8
//uloha 1

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int inp;

	printf("Zadajte prirodzene neparne cislo\n");
	scanf_s("%d", &inp);

	/*if (inp % 2 == 1 && inp <= 15) {
		for (int i = 0; i < inp; i++) {
			//printf("i = %d\n", i);
			for (int r = 0; r < inp; r++) {
				//printf("r = %d\n", r);
				if (i == 0 || i == inp - 1) {
					printf("x");
				}
				else if (i == 1 && i < r + 1) {
					printf(".");

					if (r == inp - 1) {
						printf("x");
					}
				}
				if (i == 2) {
					if (r < inp - 2) {
						printf("x");
					}
					else if (r == inp - 1 && inp != 3) {
						printf(".x");
					}
				}

			}
			printf("\n");
		}
	}
	else {
		printf("wrong input");

	}*/

	if (inp == 1) {
		printf("\nX");
	}
	else if (inp == 3) {
		printf("\nXXX"
			"\n..X"
			"\nXXX");
	}
	else if (inp == 5) {
		printf("\nXXXXX"
			"\n....X"
			"\nXXX.X"
			"\nX...X"
			"\nXXXXX");
	}
	else if (inp == 7) {
		printf("\nXXXXXXX"
			"\n......X"
			"\nXXXXX.X"
			"\nX...X.X"
			"\nX.XXX.X"
			"\nX.....X"
			"\nXXXXXXX");
	}
	else if (inp == 9) {
		printf("\\nXXXXXXXXX"
			"\n........X"
			"\nXXXXXXX.X"
			"\nX.....X.X"
			"\nX.XXX.X.X"
			"\nX.X...X.X"
			"\nX.XXXXX.X"
			"\nX.......X"
			"\nXXXXXXXXX");
	}
	else if (inp == 11) {
		printf("\nXXXXXXXXXXX"
			"\n..........X"
			"\nXXXXXXXXX.X"
			"\nX.......X.X"
			"\nX.XXXXX.X.X"
			"\nX.X...X.X.X"
			"\nX.X.XXX.X.X"
			"\nX.X.....X.X"
			"\nX.XXXXXXX.X"
			"\nX.........X"
			"\nXXXXXXXXXXX");
	}
	else if (inp == 13) {
		printf("\nXXXXXXXXXXXXX"
			"\n............X"
			"\nXXXXXXXXXXX.X"
			"\nX.........X.X"
			"\nX.XXXXXXX.X.X"
			"\nX.X.....X.X.X"
			"\nX.X.XXX.X.X.X"
			"\nX.X.X...X.X.X"
			"\nX.X.XXXXX.X.X"
			"\nX.X.......X.X"
			"\nX.XXXXXXXXX.X"
			"\nX...........X"
			"\nXXXXXXXXXXXXX");
	}
	else if (inp == 15) {
		printf("\nXXXXXXXXXXXXXXX"
			"\n..............X"
			"\nXXXXXXXXXXXXX.X"
			"\nX...........X.X"
			"\nX.XXXXXXXXX.X.X"
			"\nX.X.......X.X.X"
			"\nX.X.XXXXX.X.X.X"
			"\nX.X.X...X.X.X.X"
			"\nX.X.X.XXX.X.X.X"
			"\nX.X.X.....X.X.X"
			"\nX.X.XXXXXXX.X.X"
			"\nX.X.........X.X"
			"\nX.XXXXXXXXXXX.X"
			"\nX.............X"
			"\nXXXXXXXXXXXXXXX");
	}

	return 0;
}