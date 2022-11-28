#include <stdio.h>

int main()
{
    int i, x;
    char str[100];

    printf("\nZadajte string:\t");
    scanf("%[^\n]", str);

    printf("\nVyberte moznost\n");
    printf("1 = Zasifrovat string.\n");
    printf("2 = Desifrovat string.\n");
    scanf("%d", &x);


    switch(x)
    {
        case 1:
            for(i = 0; (i < 100 && str[i] != '\0'); i++)
                str[i] = str[i] + 3; //Pouzivame kluc 3, takze pridame hodnotu 3 k ASCII hodnote

            printf("\nZasifrovany string: %s\n", str);
            break;

        case 2:
            for(i = 0; (i < 100 && str[i] != '\0'); i++)
                str[i] = str[i] - 3; //Pouzivame kluc 3, takze odobereme hodnotu 3 k ASCII hodnote

            printf("\nDesifrovany string: %s\n", str);
            break;

        default:
            printf("\nError\n");
            break;
    }
    return 0;
}
