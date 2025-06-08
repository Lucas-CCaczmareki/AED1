#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INITIAL_SIZE    201 //200 bytes estáticos + 1 pra armazenas as pessoas
#define controlRegion   0
#define dataRegion      200

void menu(void* pBuffer, int* opt, int* i, char *tempName, char* tempAge, char *tempMail, char *nextPerson, int *totalSize, int *usedSize, int* memAmount, int* totalPeople);
void addPerson(void* pBuffer, int* i, char *tempName, char* tempAge, char *tempMail, char *nextPerson, int *totalSize, int *usedSize, int* memAmount, int* totalPeople);
bool enoughSize(int* totalSize, int* usedSize, int* memAmount);
void increaseSize(void* pBuffer, int* totalSize, int* usedSize, int* memAmount);
void showPeople (void* pBuffer, int* usedSize);

/*
==============================================
                TABELA TAMANHOS:
==============================================
char:           1 byte.
short int:      2 bytes.
int:            4 bytes 
long int:       8 bytes 
float:          4 bytes.
double:         8 bytes.
==============================================
*/

int main() {
    void *pBuffer = malloc(INITIAL_SIZE);
    
    //Creating control region
    int *opt = (int *)pBuffer + controlRegion;      //aloca espaço pra 1 inteiro (4 bytes)
    int *i = (int *)pBuffer + 1;                    //transforma pbuffer num ponteiro int e move 1(em termos int, ou seja 4bytes)

    int *totalSize = (int *)pBuffer + 2;
    *totalSize = INITIAL_SIZE;
    int *usedSize = (int *)pBuffer + 3;
    *usedSize = dataRegion;
    int *memAmount = (int *)pBuffer + 4;

    int *totalPeople = (int *)pBuffer + 5;
    *totalPeople = 0;
    
    //tamanho máximo pra string 50 caracteres
    //(pode ter memory leak aqui, parada de começar no byte 0)
    char *tempName = (char *)pBuffer + 24;   //coloca logo após os primeiros 2 ints 
    char *tempAge = (char *)pBuffer + 82;   //meio inútil alocar 50 caracteres aqui, pode melhorar depois
    char *tempMail = (char *)pBuffer + 132; //com esse aqui, tá ocupado até o byte 182
    
    while (true) {
        menu(&pBuffer, opt, i, tempName, tempAge, tempMail, nextPerson, totalSize, usedSize, memAmount, totalPeople);
    }
}

void menu(void** pBuffer, int* opt, int* i, char *tempName, char* tempAge, char *tempMail, char *nextPerson, int *totalSize, int *usedSize, int* memAmount, int* totalPeople) {
    printf("================= Agenda =================\n");
    printf("1. Adicionar pessoa\n");
    printf("2. Remover pessoa\n");
    printf("3. Buscar pessoa\n");
    printf("4. Listar todos\n");
    printf("5. Sair\n");
    printf("==========================================\n");
    printf("Digite sua opcao: ");
    scanf("%d", opt);

    switch (*opt) {
    case 1:
        /* Adicionar pessoa */
        addPerson(pBuffer, i, tempName, tempAge, tempMail, nextPerson, totalSize, usedSize, memAmount, totalPeople);
        break;
    
    case 2:
        /* Remove pessoa */
        printf("Remove p1");
        break;    

    case 3:
        /* Buscar pessoa */
        printf("Busca p1");
        break;

    case 4:
        /* Listar todas */
        showPeople(pBuffer, usedSize);
        break;

    case 5:
        exit(1);
        break;

    default:
        printf("Opcao invalida!");
        break;
    }

}

bool enoughSize(int* totalSize, int* usedSize, int* memAmount) {
    return (*usedSize + *memAmount) < *totalSize; //retorna true caso não tenha
}

void increaseSize(void* pBuffer, int* totalSize, int* usedSize, int* memAmount) {
    *totalSize += (*usedSize + *memAmount) - *totalSize;
    pBuffer = realloc(pBuffer, *totalSize);
}

void addPerson(void* pBuffer, int* i, char *tempName, char* tempAge, char *tempMail, char *nextPerson, int *totalSize, int *usedSize, int* memAmount, int* totalPeople) {
    
    //Aqui seria interessante eu criar uma pseudo struct
    printf("Nome: ");
    scanf("%s", tempName);

    printf("Idade: ");
    scanf("%s", tempAge);

    printf("Email: ");
    scanf("%s", tempMail);

    *memAmount = strlen(tempName) + 1 + strlen(tempAge) + 1 + strlen(tempMail) + 1;

    //ignora isso por enquanto
    //nextPerson += sizeof(temp)

    //antes de copiar pra dentro do espaço de memória, precisa realoocar com base no tamanho SE necessário
    if(enoughSize(totalSize, usedSize, memAmount)) {
        increaseSize(pBuffer, totalSize, usedSize, memAmount);
    }
    char *next = (char *)pBuffer + *usedSize;

    memcpy(next, tempName, strlen(tempName) + 1);
    //printf("%s", nextPerson);
    next += strlen(tempName) + 1;

    memcpy(next, tempAge, strlen(tempAge) + 1);
    //printf("%s", nextPerson);
    next += strlen(tempAge) + 1;

    memcpy(next, tempMail, strlen(tempMail) + 1);
    //printf("%s", nextPerson);
    next += strlen(tempMail) + 1;

    *usedSize += *memAmount;
    *totalPeople += 1;

}

void showPeople (void* pBuffer, int* usedSize) {
    char *p = (char *)pBuffer + dataRegion;
    char *end = (char *)pBuffer + *usedSize;

    if( p >= end ) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    while( p < end ){
        printf("-----------------------\n");
        printf("Nome: %s\n", p); //imprime os caracteres desde aonde p aponta até o \0
        p += strlen(p) + 1;      //strlen funciona igual o print, então pula até a letra após o \0 do nome;

        printf("Idade: %s\n", p);
        p += strlen(p) + 1;

        printf("Email: %s\n", p);
        p += strlen(p) + 1;
        printf("-----------------------\n");
    } 
}