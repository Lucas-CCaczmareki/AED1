#include <stdio.h>
#include <stdlib.h>

/*
====================================================
Main
2. Fac¸a um programa que receba do usuario um arquivo texto e mostre na tela quantas ´
linhas esse arquivo possui.
====================================================
*/

int main( void ) {
    int     line = 0;
    FILE*   fp;
    char    text[30];

    if( ( fp = fopen("line.txt", "r") ) == NULL ) {
        printf( "Error while opening the file!" );
        return 1;
    }

    //fgets lê n-1 (30-1) caracteres da linha do arquivo
        //retorna o pnteiro passado (ou seja o nome da string) em caso de sucesso
        //Em caso de erro ou EOF (end of file) ele retorna NULL
    //Dessa maneira, loopo até o final o arquivo e consigo as n linhas
        //PS: Se a última linha for um espaço em branco (sem \n), ele não conta ela.
    while ( fgets(text, 30, fp) != NULL ){
        line++;
    }
    fclose(fp);

    printf( "This arquive has %d lines!", line );
    return 0;
}