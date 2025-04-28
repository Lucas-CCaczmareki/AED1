// Faça um programa que armazena nomes
// O programa deve armazenar todos na mesma string
// O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos.
    //Não pode ter desperdício de memória

//Faça o seguinte menu: 
    //1- Adicionar nome
    //2- Remover nome
    //3- Listas
    //4- Sair

#define TAM 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addNome(char *nomes);
int menu();

int main(){
    char *nomes = malloc(TAM);
    nomes[0] = '\0'; //Inicializa a string com vazio, pra n dar problema com o strcat
    int opc;
    
    while(1){
        opc = menu();
        switch(opc){
            case 1:
                nomes = addNome(nomes);
            break;
    
            case 2:
                //ainda não implementado
            break;
    
            case 3:
                printf("%s", nomes);
            break;
    
            case 4:
                free(nomes);
                return 0;
            break;
    
            default:
                printf("Opção inválida\n");
            break;
    
        }
    }
}
    
int menu(){
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
    
char *addNome(char *nomes){
    char temp[TAM]; //ao declarar dessa forma, temp automaticamente libera a memória após finalizar a função

    printf("Digite nome: ");
    getchar();
    fgets(temp, TAM, stdin);
    //O segredo ta em realocar o espaço aqui sempre que adicionar uma nova string
    //o tamanho atual + o tamanho que vai ser adicionado + 1 pro \0
        //size_t é um tipo usado para guardar tamanhos
    size_t novoTam = sizeof(nomes) + sizeof(temp) + 1;
    nomes = realloc(nomes, novoTam); 

    strcat(nomes, temp);

    return nomes;
}
    
/*
void removeNome(char *nomes){
    int i;

    char *remove;

    printf("Digite nome a ser removido: ");
    getchar();
    fgets(remove, TAM, stdin);

    for(i = 0; i != '\0'; i++){
        if(remove[0] == nomes[i]){
            while(nomes[i] != '\n'){

            }
        }
    }
}
*/  