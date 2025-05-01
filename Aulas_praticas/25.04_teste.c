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
void *removeNome(char *nomes);
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
                nomes = removeNome(nomes);
            break;
    
            case 3:
                printf("%s", nomes);
            break;
    
            case 4:
                free(nomes);
                return 0;
            break;
    
            default:
                printf("Opcao invalida\n");
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
    printf("-------------------------------\n\n");
    printf("Digite a sua opcao: ");
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
    

void *removeNome(char *nomes){
    int i, j = 0, pos_remove, f_nomedif = 0;

    char remove[TAM];

    printf("Digite nome a ser removido: ");
    getchar();
    fgets(remove, TAM, stdin);

    for(i = 0; nomes[i] != '\0'; i++){ // percorre toda a string
        if(remove[0] == nomes[i]){ //pode ter encontrado uma palavra
            pos_remove = i;
            while(nomes[i] != '\n'){ //enquanto não chegar no final do nome
                if(nomes[i] != remove[j]){ //testa pra ver se os nomes são diferentes
                    f_nomedif = 1; 
                    break; //posso ativar uma flag que as palavras são diferentes
                }
                i++;
                j++;
            }
            if(f_nomedif == 0){ //se a flag continuar zerada, eu sei que os nomes são iguais
                //preciso trazer todo o resto da string pra cá
                //em outras palavras, tudo que ta depois do I pra onde tá o pos_remove
                while(nomes[pos_remove] != '\0'){
                    //i termina na \n do nome que eu to removendo.
                    //i + 1 puxa a primeira letra ou o \0, pra evitar que fique dois \n
                    nomes[pos_remove] = nomes[i + 1]; 
                    i++;
                    pos_remove++;
                }
                nomes[pos_remove] = '\0';
                printf("Nome removido com sucesso!\n");
                return nomes;
            } else {
                //se os nomes forem diferentes, ex Anabelle e Ana.
                f_nomedif = 0; //zera a flag pra caso o nome esteja mais pro final da string.
                j = 0; //zera o contador que percorre uma das palavras.
                //pos_remove meio que fodase
            }
        }
    }
    printf("Esse nome nao esta contido na string!\n");
    return nomes;
}
