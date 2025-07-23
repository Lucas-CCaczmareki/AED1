#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main () {
    Stack intStack;
    initStack(&intStack, sizeof(int));

    for(int i = 0; i < 5; i++){
        push(&intStack, &i);
    }
    
    for(int i = 0; i < 5; i++){
        printf("%d\n", *(int*)peek(&intStack));
        free(pop(&intStack));
    }
    system("pause"); // Pausa o terminal no Windows
}