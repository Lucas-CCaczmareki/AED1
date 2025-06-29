//Exercício de pilha! 1717
//Pilha
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INITIAL_CAPACITY 100

typedef struct {
    char* data;    //vetor de caracteres
    int top;
    int capacity;
} Stack;

//Chamada das funções
//as funções sempre esperam um ponteiro para stack, a fim de modificar sempre a pilha original passada como parâmetro
void initStack(Stack* stack, int tam_s);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, char value);
char pop(Stack *stack);
char peek(Stack *stack);
int maximumGain(char* s, int x, int y);

int main () {
    char *s = {"aabbabkbbbfvybssbtaobaaaabataaadabbbmakgabbaoapbbbbobaabvqhbbzbbkapabaavbbeghacabamdpaaqbqabbjbababmbakbaabajabasaabbwabrbbaabbafubayaazbbbaababbaaha"};
    int x = 1926,
        y = 4320,
        score = 0;
        
    //printf("%s\n", s);
    score = maximumGain(s, x, y);
    printf("%d", score);
}

int maximumGain(char* s, int x, int y) {
    int score = 0;
    int tam_s = strlen(s);
    Stack stack_s;
    initStack(&stack_s, tam_s);

    for(int i = 0; i < tam_s; i++) {
        //primeiro precisa testar se tá buscando um x(ab) ou um y(ba)
        if (x > y) {
            //faz a lógica pra ab
            if(isEmpty(&stack_s)){
                push(&stack_s, s[i]);
            } else {
                if(peek(&stack_s) == 'a' && s[i] == 'b'){
                    push(&stack_s, s[i]);
                    pop(&stack_s);
                    pop(&stack_s);
                    score += x;
                    continue; //pula o resto dos comandos do loop
                } else {
                    push(&stack_s, s[i]);
                }
            }
            
            if(peek(&stack_s) == 'a' && s[i+1] == 'b'){
                i++;
                push(&stack_s, s[i]);
                pop(&stack_s);
                pop(&stack_s);
                score += x;
            }
        } else {
            //faz a lógica pra ba
            if(isEmpty(&stack_s)){
                push(&stack_s, s[i]);
            } else {
                if(peek(&stack_s) == 'b' && s[i] == 'a'){
                    push(&stack_s, s[i]);
                    pop(&stack_s);
                    pop(&stack_s);
                    score += y;
                    continue; //pula o resto dos comandos do loop
                } else {
                    push(&stack_s, s[i]);
                }
            }
            //aq ele ta botando o prox a antes de ver q com o b q ja ta na pilha ele forma um ba
            if(peek(&stack_s) == 'b' && s[i+1] == 'a'){
                i++;
                push(&stack_s, s[i]);
                pop(&stack_s);
                pop(&stack_s);
                score += y;
            }
        }
    }
    //agora só faltou a lógica de desempilhar em outra e fazer ao contrário
    Stack aux_stack;
    initStack(&aux_stack, stack_s.top + 1);
    while (!isEmpty(&stack_s)) {
        if (x > y) {
            //lógica pra ab invertida (esse agora ta retirando os ba)
            push(&aux_stack, pop(&stack_s));
            if(isEmpty(&stack_s)){
                break;
            }

            if(peek(&stack_s) == 'b' && peek(&aux_stack) == 'a') {
                push(&aux_stack, pop(&stack_s));
                pop(&aux_stack);
                pop(&aux_stack);
                score += y;
            }
        } else {
            //lógica pra ba invertida, ta tirando os ab
            push(&aux_stack, pop(&stack_s));
            if(isEmpty(&stack_s)){
                break;
            }

            if(peek(&stack_s) == 'a' && peek(&aux_stack) == 'b') {
                push(&aux_stack, pop(&stack_s));
                pop(&aux_stack);
                pop(&aux_stack);
                score += x;
            }
            
        }
    }

    return score;
}

/* Lógica do programa (brainstorm)
posso fazer 2 pilhas: 1 pra empilhar o índice de ba e outra pra empilhar os índices de ab.
Ai todo "pop" que eu fizer em algumas dessas pilhas soma x ou y numa variável chamada "gain" ou algo do tipo.

Só tem um problema, como eu defino qual ba ou ab eu vou mandar pro caralho primeiro?
E a remoção de um implica na formação de outro dentro da string.

bom, desconsiderando essa lógica, o melhor seria remover aquele que tem a maior pontuação primeiro, x sempre representa AB e y sempre o BA. se x > y, mandamo os ab pro caralho primeiro, se não, manda os ba pro caralho primeiro. Acho q é o melhor q da pra fazer

ok, agora como q a gente faz isso com pilha? Last in First Out
se eu empilhar a string ai eu vou desempilhando e empilhando em outra e testando?
acho que dá

"cdbcbbaaabab"
empilha c, d, b, c, b, b, a (ultimo era um b e achou um a, empilha o a, desempilha 2, e continua) (score = 5)

cdbcb, a (mesma coisa) (score = 10)
cdbc, a, b (ultimo era um a, achou um b, empilha o b, desempilha 2 e continua) (score = 14)
cdbc, a
cdbc, a, b (ultimo era um a, achou um b, empilha o b, desempilha 2 e continua) (score = 18)

não deu o score máximo se eu n seguir a ordem. vamo tentar seguindo a ordem ( se x > y, senão)
"cdbcbbaaabab"
empilhando
c,
cd,
cdb,
cdbc,
cdbcb,
cdbcbb,
cdbcbba, (ultimo b, empilha a, desempilha 2, score(0) += 5)
cdbcba, (ultimo b, empilha a, desempilha 2, score(5) += 5)
cdbca,
cdbcab, (n é um ba, n faz nada)
cdbcaba, (ultimo b, empilha a, desempilha 2, score(10) += 5)
cdbcab, (n é um ba, n faaz nada)

fim da string.

agora desempilha procurando um ab?
desempilhando
b,
ba, (tá inverso, então ele identifica de algum jeito como ab e da pop dos 2, e soma 5 (score=19))
c
cb
cbd
cbdc

não acha nada não faz porra nenhuma, retorna o score (já q a string restante pouco me importa)

blz, assim o score fica certinho, então dá pra fazer a lógica com duas pilhas (primeiro empilha da esquerda pra direita da string) e depois desempilha, empilhando em outro canto e conferindo o inverso. 
*/

/* OK
initStack
inicializa uma pilha vazia com base em um espaço de memória já criado
*/
void initStack(Stack *stack, int tam_s) {
    stack->capacity = tam_s;
    stack->data = (char*)malloc(stack->capacity * sizeof(char));
    stack->top = -1; //Atribui o -1(espaço inexistente) pra identificar pilha vazia
}

/* OK
isEmpty
testa se o top está em -1 para ver se a pilha está vazia e retorna o resultado
*/
bool isEmpty(Stack *stack) {
    return stack->top == -1; //retorna o V ou F da comparação
}

/* OK
isFull
testa se o top está na última posição da pilha, e retorna verdadeiro ou falso
*/
bool isFull(Stack *stack) {
    //vai até capacity -1 sla n lembro pq
    return stack->top == stack->capacity - 1; //retorna o resultado da comparação
}

/*
push
Empilha um valor novo na pilha caso seja possível
*/
void push(Stack *stack, char value) {
    if(isFull(stack)) {
        printf("Algo de errado aconteceu!");
    }
    stack->data[++(stack->top)] = value; //incrementa o topo e adiciona o caracter na próxima posição livre
}

/* OK
pop
Desempilha o último elemento da pilha (o topo, na lógica FIFO) caso seja possível
*/
char pop(Stack *stack) {
    if(isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    return stack->data[(stack->top)--]; //retorna o topo e diminui o topo em uma posição, jogando ele pro universo
}

/* OK
peek
Retorna o valor do último elemento da pilha (topo) sem alterar a estrutura de dados
*/
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf( "Erro: Pilha vazia!\n" );
        exit(1);
    }
    return stack->data[stack->top]; //retorna o valor do topo
}

/* OK
freeStack
Libera a memória alocada dinâmicamente pra qualquer pilha ou string q tenha sido usada
*/
void freeStack(Stack* stack) {
    free(stack->data); //libera o vetor de caracteres
}
