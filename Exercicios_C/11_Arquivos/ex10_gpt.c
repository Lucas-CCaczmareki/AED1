#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *in, *out;
    char arqNameInput[40], arqNameOutput[40],
         city[41], mostPopCity[41];

    int population, largestPop = 0;

    printf("Type the input file name: ");
    scanf(" %s", arqNameInput);

    if ((in = fopen(arqNameInput, "r")) == NULL) {
        printf("Error while opening the input file\n");
        return 1;
    }

    printf("Type the output file name: ");
    scanf(" %s", arqNameOutput);

    if ((out = fopen(arqNameOutput, "w")) == NULL) {
        printf("Error while opening the output file\n");
        return 1;
    }

    while (fscanf(in, "%40c%d\n", city, &population) == 2) {
        city[40] = '\0';  // termina a string

        // remover espaços do final
        for (int i = 39; i >= 0 && city[i] == ' '; i--) {
            city[i] = '\0';
        }

        if (population > largestPop) {
            largestPop = population;
            strcpy(mostPopCity, city);
        }
    }

    fprintf(out, "%s %d\n", mostPopCity, largestPop);

    fclose(in);
    fclose(out);

    return 0;
}
