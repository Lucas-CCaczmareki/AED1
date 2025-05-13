#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
============================================
Main
. Fac¸a um programa que leia o conteudo de um arquivo e crie um arquivo com o mesmo ´
conteudo, mas com todas as letras min ´ usculas convertidas para mai ´ usculas. Os no- ´
mes dos arquivos serao fornecidos, via teclado, pelo usu ˜ ario. A func¸ ´ ao que converte ˜
maiuscula para min ´ uscula ´ e o toupper(). Ela ´ e aplicada em cada caractere da string.
============================================
*/

int main( void ) {
    char nome_origem[30], nome_destino[30];
    char c;
    FILE* origem;
    FILE* destino;

    printf( "Qual arquivo voce deseja deixar todo em maiúsculo? " );
    scanf( " %s", nome_origem ); //assim o nome não armazena o \n

    printf( "Em qual arquivo voce deseja armazenas a nova versao? " );
    scanf( " %s", nome_destino );

    if( ( origem = fopen(nome_origem, "r") ) == NULL ) {
        printf("Erro ao abrir o arquivo!");
    }
    if( ( destino = fopen(nome_destino, "w") ) == NULL ){
        printf("Erro ao abrir o arquivo!");
    }

    while( ( c = fgetc(origem) ) != EOF ) {
        c = toupper(c);
        fputc(c, destino);
    }
    fclose(origem);
    fclose(destino);
}