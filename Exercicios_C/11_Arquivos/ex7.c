#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
==============================================
Main
. Fac¸a um programa que receba do usuario um arquivo texto. Crie outro arquivo texto ´
contendo o texto do arquivo de entrada, mas com as vogais substitu´ıdas por ‘*’.
==============================================
*/

int main( void ) {
    FILE* in = fopen("line.txt", "r");
    FILE *out = fopen("out.txt", "w");

    char c, vogais[11] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', '\0'};

    while( ( c = fgetc(in) ) != EOF ) {
        if( strchr(vogais, c) != NULL ) { //isso significa que c é uma vogal, pois encontramos um ponteiro que não seja null
            fputc('*', out);
        } else { 
            fputc(c, out);
        }
    }
    fclose(in);
    rewind(out);

    //por algum motivo esse printf caracter a caracter não funciona :(
    while ( ( c = fgetc(out) ) != EOF ) {
        printf("AAAAAAAAAA");
        printf("%c", c); //printa o texto modificado caracter à caracter
    }
    fclose(out);
}