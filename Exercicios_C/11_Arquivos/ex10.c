#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h> 

/*
================================================================
Main
10. Fac¸a um programa que receba o nome de um arquivo de entrada e outro de sa´ıda. O
arquivo de entrada contem em cada linha o nome de uma cidade (ocupando 40 caracte- ´
res) e o seu numero de habitantes. O programa dever ´ a ler o arquivo de entrada e gerar ´
um arquivo de sa´ıda onde aparece o nome da cidade mais populosa seguida pelo seu
numero de habitantes
================================================================
*/

int main ( void ) {
    FILE* in;
    FILE* out;
    char arqNameInput[40], arqNameOutput[40],
         city[41], mostPopCity[41];

    int population, largestPop = 0;

    system("cls");

    printf( "Type the input file name: " );
    scanf( " %s", arqNameInput );


    //Explicação rápida sobre o debug, com o fileDirname ele trabalha com o a.exe dentro do diretório q eu to
    //e manda as coisas pra cá, só que ai com arquivos eu preciso ter o .txt dentro da pasta q o debugger acessa
    // que nesse caso não é a output, é a 11_Arquivos. e ele me retorna o txt aqui dentro tbm.
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("DEBUG - Current working directory: %s\n", cwd);
    

    if( ( in = fopen(arqNameInput, "r") ) == NULL ){
        printf( "Error while opening the file" );
        return 1;
    }

    printf( "Type the output file name: " );
    scanf( " %s", arqNameOutput );
    
    if( ( out = fopen(arqNameOutput, "w") ) == NULL ){
        printf( "Error while opening the file" );
        return 1;
    }
    //considerando que Deus escreveu meu arquivo corretamente com as cidades ocupando os 40 caracteres certinhos:

    //essa linha signifca que ele lerá 40 caracteres do "in" e depois lerá um número inteiro
    while( fscanf(in, "%40c%d\n", city, &population) == 2 ) { //fscanf retorna o número de itens que ele conseguiu analisar corretamente, se = 2, continuamos
        city[40] = '\0';

        if( population > largestPop ) {
            largestPop = population;
            strcpy(mostPopCity, city);
        }
    }
    fprintf( out, "%s %d", mostPopCity, largestPop );
    
    return 0;
}