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


//INCOMPLETO, REVISAR O BÁSICO DE ARQUIVOS AMANHA
int main ( void ) {
    FILE *arq = fopen("arq.txt", "a+");
    char c = 'a';

    while( c != '0' ) {
        printf( "Write a character! (0 to stop writing): ");
        scanf( " %c", &c );
        fwrite(&c, sizeof(char), 1, arq);
    }

    rewind(arq);
    while(fgets(&c, 1, arq) != 'EOF') {
        printf("%c\n", &c);
    }

}