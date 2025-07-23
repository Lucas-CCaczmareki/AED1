#ifndef STACK_H //inicia o include guard, pra evitar incluir várias vezes
#define STACK_H

#include <stdbool.h>
#include <stddef.h> //necessário pra ter o size_t

typedef struct {
    void** elements;
    int top;
    int capacity;
    size_t elementSize;
} Stack;

//protótipos das funções. É o contrato pro .c ter que implementar isso
void initStack(Stack* stack, size_t elementSize);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, const void* value);
void* pop(Stack *stack);
void* peek(Stack *stack);


#endif //finaliza o include guard