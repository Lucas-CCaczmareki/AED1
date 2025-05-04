#include <stdio.h>
#include <stdlib.h>

/*
=========================================================
Main
1. Crie um programa que:
(a) Aloque dinamicamente um array de 5 numeros inteiros, ´
(b) Pec¸a para o usuario digitar os 5 n ´ umeros no espac¸o alocado, ´
(c) Mostre na tela os 5 numeros, ´
(d) Libere a memoria alocada
=========================================================
*/

int main( void ) {
    int *array, i;
    array = (int *)malloc(sizeof(int)*5);

    if ( array = NULL ) {
        printf("Erro ao alocar memória!");
        return 1;
    }

    for( i = 0; i < 5; i++) {
        printf( "Digite um numero: " );
        scanf( "%d", &array[i] );
        //array++;
    }

    for( i = 0; i < 5; i++ ) {
        printf( "\nNumero: %d", array[i] );
        //array++;
    }
    
    free(array);
    return 0;
}