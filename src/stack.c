// stack.c

#include "stack.h" // Inclui o cabeçalho da própria pilha
#include <stdio.h>   // Para printf, perror
#include <stdlib.h>  // Para malloc, realloc, free, exit
#include <string.h>  // Para memcpy

// Definição interna para a capacidade inicial (pode ser #define aqui ou em .h)
#define INITIAL_CAPACITY 10

//A partir daqui, copio a implementação das funções da pilha...

/*
initStack
inicializa uma pilha vazia com base em um espaço de memória já criado
*/
void initStack(Stack *stack, size_t elementSize) {
    stack->capacity = INITIAL_CAPACITY;
    stack->elements = (void**)malloc(stack->capacity * sizeof(void*));
    
    if (stack->elements == NULL) {
        printf("Erro ao alocar a memória para a pilha");
        exit(1);
    }

    stack->top = -1; //"índice" da pilha
    stack->elementSize = elementSize;
}

/*
isEmpty
testa se o top está em -1 para ver se a pilha está vazia e retorna o resultado
*/
bool isEmpty(Stack *stack) {
    return stack->top == -1; //retorna o V ou F da comparação
}

/*
isFull
testa se o top está na última posição da pilha, e retorna verdadeiro ou falso
*/
bool isFull(Stack *stack) {
    //o array pilha de tamanho CAPACITY vai sempre até CAPACITY -1 por definição
    return stack->top == stack->capacity - 1; //retorna o resultado da comparação
}

/*
resize
Doubles the capacity of the stac if needed.
The use of static here is a good practice. It makes it private for stack.c
*/
static void resize(Stack* stack) {
    stack->capacity *= 2; //seria muito custoso em tempo aumentar de 1 em 1
    stack->elements = (void**)realloc(stack->elements, stack->capacity * sizeof(void*));

    if (stack->elements == NULL) {
        printf("Erro ao realocar memória para a pilha!");
        exit(1);
    }
}

/*
push
Empilha um valor novo na pilha caso seja possível
*/
void push(Stack *stack, const void* value) {
    if(isFull(stack)) {
        resize(stack);
    }
    stack->top++;
    stack->elements[stack->top] = malloc(stack->elementSize); //cria um espaço para o elemento que vai ser apontado
    
    if (stack->elements[stack->top] == NULL) {
        printf("Erro ao alocar memória para o elemento");
        exit(1);
    }
    
    memcpy(stack->elements[stack->top], value, stack->elementSize);
    //faz uma cópia do valor para qual o endereço recebido pelo push aponta

}

/*
pop
Desempilha o último elemento da pilha (o topo, na lógica FIFO) caso seja possível
*/
void* pop(Stack *stack) {
    if(isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    void* data = stack->elements[stack->top];
    stack->elements[stack->top] = NULL; //evita que fique qualquer ponteiro pro nada
    stack->top--; //diminui a pilha efetivamente
    return data;    //retorna o ponteiro pro dado retirado
                    //Quem chamou a função é responsável por liberar esse ponteiro
}

/*
peek
Retorna o valor do último elemento da pilha (topo) sem alterar a estrutura de dados
*/
void* peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    return stack->elements[stack->top]; //retorna o valor do topo
}

/*
freeStack
Libera a memória alocada dinâmicamente pra qualquer pilha ou string q tenha sido usada
*/
void freeStack(Stack* stack) {
    for( int i = 0; i <= stack->top; i++ ) {
        free(stack->elements[i]); //libera a memória de cada elemento
    }
    free(stack->elements); //libera o vetor de ponteiros pros elementos
    
    //Opcional, mas é uma boa liberar
    stack->elements = NULL;
    stack->top = -1;
    stack->capacity = 0;
}