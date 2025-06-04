#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INITIAL_CAPACITY 100

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
int evalRPN(char** tokens, int tokensSize);

int main() {
    
    char *tokens[] = {"4","-2","/","2","-3","-","-"};

    //quantidade de elementos
    //tamanho do vetor em bytes / tamanho de 1 elemento do vetor em bytes = número de elementos do vetor
    int size = sizeof(tokens) / sizeof(tokens[0]);

    int result = evalRPN(tokens, size);
    printf("Resultado: %d\n", result); // Deve imprimir 9
    
   
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

/*
isNumber
returns if a string is a valid number or not
*/
bool isNumber(const char* str) {
    if(*str == '-' || *str == '+') {
        str++; //aponta pro próximo caracter, avançando o ponteiro
    }

    //se a string era só um operador, retorna falso.
    if(*str == '\0') {
        return false;
    }

    while( *str != '\0' ) {
        //quebra e retorna falso se n for dígito
        if(isdigit(*str) == false) {
            return false;
        }
        str++; //aponta pro próximo caracter
    }
    return true;
    //  
}  

/*
evalRPN

*/
int evalRPN(char** tokens, int tokensSize) {
    Stack s_op;    //cria uma pilha pra armazenar os tokens e outra para fazer as operações
    
    initStack(&s_op);

    char temp[20];
    int a, b, result;

    //Agora da um pop e armazena na s_op até achar um caracter não númerico
    for( int i = 0; i < tokensSize; i++ ) {
        //Se o topo da token é um número
        if( isNumber(tokens[i]) ) {
            push(&s_op, strdup(tokens[i])); //move pra nova estrutura
        } else {
            b = atoi(pop(&s_op));
            a = atoi(pop(&s_op));

            //Se não é um número, ou seja, é um operador
            if ( strcmp(tokens[i], "+") == 0 ) result = a + b;
            else if ( strcmp(tokens[i], "-") == 0) result = a - b;
            else if ( strcmp(tokens[i], "*") == 0) result = a * b;
            else if ( strcmp(tokens[i], "/") == 0) result = a / b;

            snprintf(temp, sizeof(temp), "%d", result);
            push(&s_op, strdup(temp));
        }
    }

    result = atoi(peek(&s_op));
    freeStack(&s_op);
    return result;
}