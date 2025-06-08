#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INITIAL_SIZE    201 //200 bytes estáticos + 1 pra armazenas as pessoas
#define controlRegion   0
#define dataRegion      200

#define OPT (int *)pBuffer + controlRegion
#define TOTALSIZE (int *)pBuffer + 1
#define USEDSIZE (int *)pBuffer + 2
#define MEMAMOUNT (int *)pBuffer + 3
#define TOTALPEOPLE (int *)pBuffer + 4
#define TEMPNAME (char *)pBuffer + 24
#define TEMPAGE (char *)pBuffer + 82
#define TEMPMAIL (char *)pBuffer + 132

bool alreadyIn(void* pBuffer, char* tempName, int* usedSize, char* p, char* end, int* totalPeople);

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


int main( void ) {
    void *pBuffer = malloc(INITIAL_SIZE);
    
    //Creating control region (this has to be called at every realloc)
    int *opt = OPT;
    int *totalSize = TOTALSIZE;
    int *usedSize = USEDSIZE;
    int *memAmount = MEMAMOUNT;
    int *totalPeople = TOTALPEOPLE;

    char *tempName = TEMPNAME;
    char *tempAge = TEMPAGE;
    char *tempMail = TEMPMAIL;

    char *p = (char *)pBuffer + dataRegion; //points to the begging of data region
    char *end = (char *)pBuffer + *usedSize; //points to the end of data region
    //=================================================================
    //Setting initial values
    *totalSize = INITIAL_SIZE;
    *usedSize = dataRegion;
    *totalPeople = 0;

    //=================================================================

    //========================== MENU =================================
    while (true) {
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
            /* ====================== Adicionar pessoa ====================== */
            getchar();
            printf("Email: ");
            scanf("%[^\n]s", tempMail);
            
            getchar(); //tira o \n do buffer do teclado
            printf("Nome: ");
            scanf("%[^\n]s", tempName);

            getchar();
            printf("Idade: ");
            scanf("%s", tempAge);

            if(alreadyIn(pBuffer, tempMail, usedSize, p, end, totalPeople)) {
                printf("Essa pessoa ja esta na agenda!\n");
            } else {
                *memAmount = strlen(tempName) + 1 + strlen(tempAge) + 1 + strlen(tempMail) + 1;
                //if not enought memory, realocate with more
                if(!( (*usedSize + *memAmount) <= *totalSize )) {   
                    //increase total memory
                    *totalSize += (*usedSize + *memAmount - *totalSize);
                    pBuffer = realloc(pBuffer, *totalSize);
                    
                    //update pointers
                    opt = OPT;
                    totalSize = TOTALSIZE;
                    usedSize = USEDSIZE;
                    memAmount = MEMAMOUNT;
                    totalPeople = TOTALPEOPLE;

                    tempName = TEMPNAME;
                    tempAge = TEMPAGE;
                    tempMail = TEMPMAIL;
                }

                //points to the next free space
                char *next = (char *)pBuffer + *usedSize;
                
                memcpy(next, tempMail, strlen(tempMail) + 1);
                next += strlen(tempMail) + 1;

                memcpy(next, tempName, strlen(tempName) + 1); //+1 to capture \0
                next += strlen(tempName) + 1; //points right after \0

                memcpy(next, tempAge, strlen(tempAge) + 1);
                next += strlen(tempAge) + 1;

                *usedSize += *memAmount;
                *totalPeople += 1;
            }
            /* ================================================================ */
            break;
        
        case 2:
            /* Remove pessoa */
            printf("Remove p1");
            break;    

        case 3:
            /* ====================== Busca pessoa ====================== */
            getchar();
            printf("Quem voce deseja buscar? (digite email): ");
            scanf("%[^\n]s", tempMail);
            
            p = (char *)pBuffer + dataRegion;
            end = (char *)pBuffer + *usedSize;

            if(*totalPeople == 0) {
                printf("Pessoa nao encontrada!\n\n");
                break;
            }

            while( p <= end ) {
                if(strcmp(tempMail, p) == 0) {
                    printf("--------------------------\n");
                    printf("Email: %s\n", p);
                    p += strlen(p) + 1;

                    printf("Nome: %s\n", p);
                    p += strlen(p) + 1;

                    printf("Idade: %s\n", p);
                    p += strlen(p) + 1;
                    printf("--------------------------\n");
                    break;
                } else if(p == end) {
                    printf("Pessoa nao encontrada!\n\n");
                    break;
                } else {
                    //I could do this in a loop. Would be easier if someone wants to add new informations for each person
                    //jumps 3 (name, age and mail) \0 to the next name
                    p += strlen(p) + 1;
                    p += strlen(p) + 1;
                    p += strlen(p) + 1; //at here, p points to the next name
                }
            }
            break;
            /* ========================================================== */

        case 4:
            /* ====================== Listar todas ====================== */
            p = (char *)pBuffer + dataRegion;
            end = (char *)pBuffer + *usedSize;

            if(*totalPeople == 0) { //if there is no people in the agenda
                printf("Agenda vazia!\n");
            } else {
                while( p < end ) { //while the memory address is before end
                    printf("--------------------------\n");
                    printf("Email: %s\n", p); //prints the chars from p til the first \0
                    p += strlen(p) + 1;      //strlen return the amount of chars til the first \0, so p now points right after \0 (cuz +1)

                    printf("Nome: %s\n", p);
                    p += strlen(p) + 1;

                    printf("Idade: %s\n", p);
                    p += strlen(p) + 1;
                    printf("--------------------------\n");
                }
            }
            /* ========================================================== */
            break;

        case 5:
            exit(1);
            break;

        default:
            printf("Opcao invalida!");
            break;
        }
    }
    
}

bool alreadyIn(void* pBuffer, char* tempMail, int* usedSize, char* p, char* end, int* totalPeople) {
    p = (char *)pBuffer + dataRegion;
    end = (char *)pBuffer + *usedSize;

    if(*totalPeople == 0) {
        return false;
    } else {
        while( p < end ) {
            if(strcmp(tempMail, p) == 0) {
                return true;
            } else {
                //jumps 3 (mail, name and age) \0 to the next nmail
                p += strlen(p) + 1;
                p += strlen(p) + 1;
                p += strlen(p) + 1; //at here, p points to the next mail
            }
        }
    }
    return false;
}