/*
DR MEMORY: OK 
RESTRIÇÕES: Só da uma verificada se na tua função tu n acaba copiando e usando outra área da memória
COMMENTS & IDENTATION: OK
VIDEO: NOT DONE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INITIAL_SIZE    201 //200 bytes estáticos + 1 pra armazenas as pessoas
#define controlRegion   0
#define dataRegion      200

#define OPT             (int *)pBuffer + controlRegion
#define TOTALSIZE       (int *)pBuffer + 1
#define USEDSIZE        (int *)pBuffer + 2
#define MEMAMOUNT       (int *)pBuffer + 3
#define TOTALPEOPLE     (int *)pBuffer + 4
#define TEMPNAME        (char *)pBuffer + 24
#define TEMPAGE         (char *)pBuffer + 82
#define TEMPMAIL        (char *)pBuffer + 132
#define GENERICPOINTER  (char *)pBuffer + dataRegion;
#define ENDDATA         (char *)pBuffer + *usedSize;

char* searchPerson(void** pBuffer, char* tempName, int* usedSize, char* p, char* end, int* totalPeople);

/* Tabela tamanho em bytes
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

/*
main
Essa função controla o pBuffer, que representa uma agenda.
pBuffer é uma área de memória que cresce ou diminui conforme adicionamos ou removemos pessoa na agenda
O programa segue as restrições de:
somente um malloc
nenhuma variável (só ponteiros para dentro de pBuffer)
*/
int main( void ) {
    void *pBuffer       = malloc(INITIAL_SIZE);
    
    //=================================================================
    //Creating control region (this has to be called at every realloc)
    int *opt            = OPT;
    int *totalSize      = TOTALSIZE;
    int *usedSize       = USEDSIZE;
    int *memAmount      = MEMAMOUNT;
    int *totalPeople    = TOTALPEOPLE;

    char *tempName      = TEMPNAME;
    char *tempAge       = TEMPAGE;
    char *tempMail      = TEMPMAIL;

    char *p             = GENERICPOINTER;   //points to the begging of data region
    char *p2            = GENERICPOINTER; 
    char *end           = ENDDATA;          //points to the end of data region
    //=================================================================
    //Setting initial values
    *totalSize          = INITIAL_SIZE;
    *usedSize           = dataRegion;
    *totalPeople        = 0;
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
            //Possíveis problemas:
                //os scanf q não limitam tamanho de leitura pode estourar minha estrutura

            getchar();                      //limpa buffer do teclado
            printf("Email: ");
            scanf("%[^\n]s", tempMail);     //lê até achar um \n(enter)
            
            getchar();                      //tira o \n do buffer do teclado
            printf("Nome: ");
            scanf("%[^\n]s", tempName);

            getchar();
            printf("Idade: ");
            scanf("%s", tempAge);          

            //Confore se a pessoa a ser adicionada já está na agenda, só executa se ela não estiver
            if(searchPerson(&pBuffer, tempMail, usedSize, p, end, totalPeople) != NULL) {
                printf("Essa pessoa ja esta na agenda!\n");

            } else {
                //Resets memAmount and calculate based on the size of that person's data
                *memAmount = 0;
                *memAmount = strlen(tempName) + 1 + strlen(tempAge) + 1 + strlen(tempMail) + 1;

                //if not enought memory, realocate with more
                if(!( (*usedSize + *memAmount) <= *totalSize )) {   
                    //increase total memory
                    *totalSize += (*usedSize + *memAmount - *totalSize);
                    pBuffer     = realloc(pBuffer, *totalSize);
                    
                    //update pointers from static area
                    opt         = OPT;
                    totalSize   = TOTALSIZE;
                    usedSize    = USEDSIZE;
                    memAmount   = MEMAMOUNT;
                    totalPeople = TOTALPEOPLE;

                    tempName    = TEMPNAME;
                    tempAge     = TEMPAGE;
                    tempMail    = TEMPMAIL;

                    p           = GENERICPOINTER;
                    p2          = GENERICPOINTER;
                    end         = ENDDATA;
                }

                //points to the next free space
                char *next = (char *)pBuffer + *usedSize;
                
                //copies from static area to date area
                memcpy(next, tempMail, strlen(tempMail) + 1);
                next += strlen(tempMail) + 1;

                memcpy(next, tempName, strlen(tempName) + 1);   //+1 to capture \0
                next += strlen(tempName) + 1;                   //points right after \0

                memcpy(next, tempAge, strlen(tempAge) + 1);
                next += strlen(tempAge) + 1;
                
                //uptade data structure area indicators
                *usedSize += *memAmount;
                *totalPeople += 1;
            }
            /* ================================================================ */
            break;
        
        case 2:
            /* ========================= Remove pessoa ======================== */
            if(*totalPeople == 0) {
                printf("Agenda vazia!\n");
            } else {
                getchar();
                printf("Quem voce deseja remover? (digite email) ");
                scanf("%[^\n]s", tempMail);
                
                //P points to the begging of the element (person) we want to remove
                //P2 starts at the same point, but will end pointing right after this element
                p   = searchPerson(&pBuffer, tempMail, usedSize, p, end, totalPeople);
                p2  = p;

                if( p2 != NULL ) {

                    //Calculates the amount of memory we will free and moves P2 to the end of element
                    *memAmount = 0;
                    *memAmount += strlen(p2) + 1;       //saves the size of the email
                    p2 += strlen(p2) + 1;
                    *memAmount += strlen(p2) + 1;       //saves the size of the name
                    p2 += strlen(p2) + 1;
                    *memAmount += strlen(p2) + 1;       //saves the size of the age
                    p2 += strlen(p2) + 1;

                    end = (char *)pBuffer + *usedSize;  //uptade end just to make sure

                    //end - p2 gives me the amount of bytes between both, cuz they are both char* (1 byte)
                    memmove(p, p2, (end - p2));         //moves every memory from "p2" til "end" to were "p" is.

                    //Realocates pbuffer based on the amount of memory removed
                    pBuffer = realloc(pBuffer, (*totalSize - *memAmount));

                    //update pointers from static area
                    opt         = OPT;
                    totalSize   = TOTALSIZE;
                    usedSize    = USEDSIZE;
                    memAmount   = MEMAMOUNT;
                    totalPeople = TOTALPEOPLE;

                    tempName    = TEMPNAME;
                    tempAge     = TEMPAGE;
                    tempMail    = TEMPMAIL;

                    p           = GENERICPOINTER;
                    p2          = GENERICPOINTER;
                    end         = ENDDATA;

                    //update data structure indicators
                    *usedSize       -= *memAmount;
                    *totalSize      -= *memAmount;
                    *totalPeople    -= 1;

                } else {
                    printf("Essa pessoa nao esta na agenda!\n");
                    break;
                }
            }
            break;    
            /* ================================================================ */

        case 3:
            /* ========================= Busca pessoa ========================= */
            if(*totalPeople == 0) {
                printf("Agenda vazia!\n");
            } else {
                getchar();
                printf("Quem voce deseja buscar? (digite email): ");
                scanf("%[^\n]s", tempMail);

                //searchPerson returns null if it didnt find anyone, or a pointer to the email if it finds
                p = searchPerson(&pBuffer, tempMail, usedSize, p, end, totalPeople);
                if(p != NULL) {
                    printf("--------------------------\n");
                    printf("Email: %s\n", p);
                    p += strlen(p) + 1;

                    printf("Nome: %s\n", p);
                    p += strlen(p) + 1;

                    printf("Idade: %s\n", p);
                    p += strlen(p) + 1;
                    printf("--------------------------\n");
                } else {
                    printf("Pessoa nao encontrada");
                }
            }

            break;
            /* ========================================================== */

        case 4:
            /* ====================== Listar todas ====================== */
            p   = GENERICPOINTER;
            end = ENDDATA;

            if(*totalPeople == 0) {             //if there is no people in the agenda
                printf("Agenda vazia!\n");
                break;
            } else {
                while( p < end ) {              //while the memory address is before end
                    printf("--------------------------\n");
                    printf("Email: %s\n", p);   //prints the chars from p til the first \0
                    p += strlen(p) + 1;         //strlen return the amount of chars til the first \0, so p now points right after \0 (cuz +1)

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
            free(pBuffer);  //frees the memory used by pBuffer
            exit(1);        //finishes the program
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    
}

/*
searchPerson
Receiver a pointer to the pointer that points to the area alocated to pBuffer, so the system doesnt create a copy of that
This function searches the data area based on a given email.
Then it return a pointer to that email if found, or NULL if not found
*/
char* searchPerson(void** pBuffer, char* tempMail, int* usedSize, char* p, char* end, int* totalPeople) {
    p   = (char *)(*pBuffer) + dataRegion;
    end = (char *)(*pBuffer) + *usedSize;

    if(*totalPeople == 0) {
        return NULL;
    } else {
        while( p < end ) {
            if(strcmp(tempMail, p) == 0) {
                return p;
            } else {
                //I could do this in a loop. Would be easier if someone wants to add new informations for each person
                //jumps 3 (mail, name and age) \0 to the next nmail
                p += strlen(p) + 1;
                p += strlen(p) + 1;
                p += strlen(p) + 1; //at here, p points to the next mail or to the end of structure
            }
        }
    }
    return NULL;
}