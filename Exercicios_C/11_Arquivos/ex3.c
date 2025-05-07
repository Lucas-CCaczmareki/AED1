#include <stdio.h>
#include <string.h>

/*
=============================================
Main
3. Fac¸a um programa que receba do usuario um arquivo texto e mostre na tela quantas ´
letras sao vogais. 
=============================================
*/

int main ( void ) {
    FILE* fp; 
    int contador = 0;
    char c, 
    //quando declara uma string dessa maneira é necessário escrever manualment o \0
    vogais[11] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', '\0'}; 

    if( ( fp = fopen( "arq.txt", "r" ) ) == NULL ) {
        printf( "Error while opening the file!" );
        return 1;
    } 

    while ( ( c = fgetc(fp) )  != EOF ) {
        //existe uma forma melhor de fazer isso com a função strchr que retorna um ponteiro 
        //caso o caractere esteja contido numa string
        /*
        if( c == 'Aa' || c == 'Ee' || c == 'Ii' || c == 'Oo' || c == 'Uu' ) {
            contador++;
        }
        */
        //printf("%c", c);
        //A função strchr retorna NULL quando NÃO encontra o caracter
        if(strchr(vogais, c) != NULL){
            contador++;
        }
    }

    printf( "Existem %d vogais no arquivo!", contador );


}