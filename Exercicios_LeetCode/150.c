#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 5000 //capacidade da pilha genérica

//Isso aqui, posteriormente é interessante criar com alocação dinâmica, mas meu objetivo no momento é só entender o funcionamento em pilha.
typedef struct {
    char* data[MAX_SIZE];
    int top;
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
void initStack(Stack* stack) {
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
    //o array pilha de tamanho MAX_SIZE vai sempre até MAX_SIZE -1 por definição
    return stack->top == MAX_SIZE - 1; //retorna o resultado da comparação
}

/*
push
Empilha um valor novo na pilha caso seja possível
*/
void push(Stack *stack, char* value) {
    if(isFull(stack)) {
        printf( "Erro: Pilha cheia!\n" );
        return;
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
    Stack s_token, s_op;    //cria uma pilha pra armazenar os tokens e outra para fazer as operações
    
    initStack(&s_token);
    initStack(&s_op);

    char temp[20];
    int a, b;

    //Preenche a s_token com os tokens
    //o mais a esquerda dos tokens é o topo, então preciso fazer com lógica invertida
    for( int i = tokensSize - 1; i >= 0; i-- ) {
        push(&s_token, tokens[i]);
        //printf("%s\n", tokens[i]);
    }

    //Agora da um pop e armazena na s_op até achar um caracter não númerico
    for( int i = 0; i < tokensSize; i++ ) {
        //Se o topo da token é um número
        if( isNumber(peek(&s_token)) ) {
            push(&s_op, pop(&s_token)); //move pra nova estrutura
        } else {
            //Se não é um número, ou seja, é um operador
            if ( strcmp( peek(&s_token), "+" ) == 0 ) {
                //retira o + da pilha token
                pop(&s_token); 
                
                b = atoi(pop(&s_op));   //segundo operando, q ta no topo
                a = atoi(pop(&s_op));   //primeiro operando, q ta embaixo

                //pop me retorna os 2 números em string que eu converto pra int com atoi e somo, convertendo de novo pra string com snprintf
                snprintf(temp, sizeof(temp), "%d", a + b);

                //joga o resultado de snprintf na pilha do resultado através de uma string temp
                push(&s_op, strdup(temp));

            } else if ( strcmp( peek(&s_token), "-" ) == 0 ) {
                //repete a lógica mudando o operador
                pop(&s_token);

                b = atoi(pop(&s_op));   //segundo operando
                a = atoi(pop(&s_op));   //primeiro operando
                
                snprintf(temp, sizeof(temp), "%d", a - b);

                //tava ocorrendo um erro de armazenar na memória devido ao parâmetro que o push recebe ser um ponteiro
                //ele armazenava aquele ponteiro de caracteres (string) que era o mesmo do temp
                //por isso quando eu modificava o temp na próxima interação, isso causava um comportamento indesejado
                //assim, eu faço uma cópia com strdup (que aloca dinamicamente) e coloco essa cópia na pilha
                //depois eu só continuo mexendo no mesmo espaço do temp.
                push(&s_op, strdup(temp));

            } else if ( strcmp( peek(&s_token), "*" ) == 0 ) {
                //repete a lógica
                pop(&s_token);

                b = atoi(pop(&s_op));   //segundo operando
                a = atoi(pop(&s_op));   //primeiro operando

                snprintf(temp, sizeof(temp), "%d", a * b);
                push(&s_op, strdup(temp));

            } else if ( strcmp( peek(&s_token), "/" ) == 0 ) {
                //repete a lógica
                pop(&s_token);

                b = atoi(pop(&s_op));   //segundo operando
                a = atoi(pop(&s_op));   //primeiro operando

                snprintf(temp, sizeof(temp), "%d", a / b);
                push(&s_op, strdup(temp));
            }
        }
    }

    int result = atoi(peek(&s_op));

    //Isso evita memory leaks
    //agora desaloca os espaços alocados com strdup
    while(!isEmpty(&s_op)) { //enquanto a s_op NÃO estiver vazia
        free(pop(&s_op));
    }

    return result;
}