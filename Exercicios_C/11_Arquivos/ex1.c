#include <stdio.h>
#include <stdlib.h>

/*
==================================================
Main
1. Escreva um programa que:
(a) Crie/abra um arquivo texto de nome “arq.txt”
(b) Permita que o usuario grave diversos caracteres nesse arquivo, at ´ e que o usu ´ ario ´
entre com o caractere ‘0’
(c) Feche o arquivo
Agora, abra e leia o
==================================================
*/

int main ( void ) {
    FILE *arq = fopen("arq.txt", "w+");
    char c = 'a';

    while( 1 ) {
        printf( "Write a character! (0 to stop writing): ");
        scanf( " %c", &c ); //esse espaço antes do %c impede a leitura do \n

        if( c == '0' ) break;

        //aqui não é necessário usar fgets ou fwrite, pois ambos são pensados para blocos de informações, strings
            //e temos funções mais compactas e legiveis pra iss como o fputc para colocar caracter dentro do arquivo, e o fgetc pra ler um caractere do arquivo
        fputc(c, arq);
        //fwrite(&c, sizeof(char), 1, arq);
    }

    rewind(arq);
    while( ( c = fgetc(arq) ) != EOF ) {
        printf("%c\n", c);
    }

    fclose( arq );
    return 0;

}