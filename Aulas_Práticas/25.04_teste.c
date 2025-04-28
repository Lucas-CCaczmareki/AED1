/*
Eu tava com um problema que o código funciona em outros compiladores, mas não no VSCode, ai mandei pro gpt e ele me retornou isso.
Arrumou os problemas, mas preciso entendê-los ainda.

Também preciso finalizar o código.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1000

char *addNome(char *nomes);
int menu();

int main() {
    char *nomes = malloc(TAM);
    if (nomes == NULL) {
        printf("Erro de memória!\n");
        return 1;
    }
    nomes[0] = '\0';  // Inicializa string vazia

    int opc;
    while (1) {
        opc = menu();
        switch (opc) {
            case 1:
                nomes = addNome(nomes);
                break;
            case 2:
                // Ainda não implementado
                break;
            case 3:
                printf("%s", nomes);
                break;
            case 4:
                free(nomes);
                return 0;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
}

int menu() {
    int opc;
    printf("--------- Menu Insano ---------\n");
    printf("\t1. Adicionar nome\n");
    printf("\t2. Remover nome\n");
    printf("\t3. Listar\n");
    printf("\t4. Sair\n");
    printf("-------------------------------\n");
    printf("Digite a sua opção: ");
    scanf("%d", &opc);
    return opc;
}

char *addNome(char *nomes) {
    char temp[TAM];

    printf("Digite nome: ");
    getchar();  // Limpa o \n pendente
    fgets(temp, TAM, stdin);

    size_t novo_tamanho = strlen(nomes) + strlen(temp) + 1;
    nomes = realloc(nomes, novo_tamanho);
    if (nomes == NULL) {
        printf("Erro de memória!\n");
        exit(1);
    }

    strcat(nomes, temp);

    return nomes;
}
