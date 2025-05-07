#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
===========================================================
Main
4. Fac¸a um programa que receba do usuario um arquivo texto e mostre na tela quantas ´
letras sao vogais e quantas s ˜ ao consoantes. 
===========================================================
*/

int main ( void ) {
    FILE *fp = fopen("arq.txt", "r");
    char c,
    vogais[11] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', '\0'}; 
    int cont_vogal = 0, cont_consoante = 0;

    while( ( c = fgetc(fp) ) != EOF ) {
        if( strchr(vogais, c) != NULL ){ //null significa que ela não encontrou uma vogal
            cont_vogal++;
        } else {
            cont_consoante++;
        }
    }

    printf( "Your arquive has %d vogals and %d consonants", cont_vogal, cont_consoante );
}