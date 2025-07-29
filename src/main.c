#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int maxChunksToSorted(int *arr, int arrSize);

int main () {
    int arr[] = {1, 0, 2, 3, 4};
    int arrSize = 5;
    int maxChunks = maxChunksToSorted(&arr, arrSize);

    printf("%d\n", maxChunks);

    system("pause");

    return 0;
}


/*
Resolve o problema usando uma pilha que só armazena os maiores números de cada chunk.
Ele empilha um número, e enquanto encontrar menores, vai formando aquela chunk.
Se achar um maior, armazena na pilha pois pode ser um possível novo chunk.

Continua percorrendo o vetor, se achar um menor que o último empilhado, testa com todos da pilha
pra ver se não é menor que o penúltimo ou anterior a isso empilhados. Se for, significa que esses números
todos formam apenas um chunk. Por isso ele desempilha tudo e deixa apenas o maior elemento do chunk.

Continua isso até chegar ao fim do vetor.
*/
int maxChunksToSorted(int *arr, int arrSize) {
    //Stack to store the maximum elements of each chunk
    Stack intStack;
    initStack(&intStack, sizeof(int));

    for (int i = 0; i < arrSize; i++) {
        //Case 1: current element is larger, starts a new chunk
        if (isEmpty(&intStack) || arr[i] > *(int*)peek(&intStack)) {
            push(&intStack, &arr[i]);
        } else {
            //Case 2: Merge chunks
            int maxElement = *(int*)peek(&intStack);
            while (!isEmpty(&intStack) && arr[i] < *(int*)peek(&intStack)) {
                free(pop(&intStack));                
            }
            push(&intStack, &maxElement);
        }
    }
    int size_stack = intStack.top + 1; //top é um índice. +1 por que o primeiro elemento é 0.
    freeStack(&intStack); //libera a memória da pilha e de seus elementos

    return size_stack;
}