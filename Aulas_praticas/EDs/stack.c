//Pilha
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INITIAL_CAPACITY 100

//I should haver implemented a struct for "data", so I could change that easily.

//Isso aqui, posteriormente é interessante criar com alocação dinâmica, mas meu objetivo no momento é só entender o funcionamento em pilha.
typedef struct {
    char** data;    //vetor de strings (ponteiro pra ponteiro de char)
    int top;
    int capacity;
} Stack;

//Chamada das funções
//as funções sempre esperam um ponteiro para stack, a fim de modificar sempre a pilha original passada como parâmetro
void initStack(Stack* stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, char* value);
char* pop(Stack *stack);
char* peek(Stack *stack);

int main() {
    Stack stack;
    initStack(&stack);
    push(&stack, "1");
    printf("%s", peek(&stack));
    return 0;
}

/*
initStack
inicializa uma pilha vazia com base em um espaço de memória já criado
*/
void initStack(Stack *stack) {
    stack->capacity = INITIAL_CAPACITY;
    stack->data = (char**)malloc(stack->capacity * sizeof(char*));
    stack->top = -1; //Atribui o -1(espaço inexistente) pra identificar pilha vazia
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
*/
void resize(Stack* stack) {
    stack->capacity *= 2; //seria muito custoso em tempo aumentar de 1 em 1
    stack->data = (char**)realloc(stack->data, stack->capacity * sizeof(char*));
}

/*
push
Empilha um valor novo na pilha caso seja possível
*/
void push(Stack *stack, char* value) {
    if(isFull(stack)) {
        resize(stack);
    }
    stack->data[++(stack->top)] = value; //incrementa o topo e adiciona na próxima posição
}

/*
pop
Desempilha o último elemento da pilha (o topo, na lógica FIFO) caso seja possível
*/
char* pop(Stack *stack) {
    if(isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    //stack->top--;
    return stack->data[(stack->top)--]; //retorna o topo e diminui o topo em uma posição, jogando ele pro universo
}

/*
peek
Retorna o valor do último elemento da pilha (topo) sem alterar a estrutura de dados
*/
char* peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    return stack->data[stack->top]; //retorna o valor do topo
}

/*
freeStack
Libera a memória alocada dinâmicamente pra qualquer pilha ou string q tenha sido usada
*/
void freeStack(Stack* stack) {
    for( int i = 0; i <= stack->top; i++ ) {
        free(stack->data[i]); //libera as strings
    }
    free(stack->data); //libera o vetor de ponteiros pra char
}