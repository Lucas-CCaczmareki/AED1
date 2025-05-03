#include <stdio.h>
#include <stdlib.h>

/*
=============================================
Main:
1. Escreva um programa que declare um inteiro, um real e um char, e ponteiros para inteiro, real, e char. 
Associe as variaveis aos ponteiros (use &). Modifique os valores de ´
cada variavel usando os ponteiros. Imprima os valores das vari ´ aveis antes e ap ´ os a ´
modificac¸ao.
=============================================
*/

int main( void ) {
    int     a = 1;
    float   b = 2.5;
    char    c = 'L';

    int*   pA = &a;
    float* pB = &b;
    char*  pC = &c;

    printf( "A = %d\n", a );
    printf( "B = %.2f\n", b );
    printf( "C = %c\n\n", c );

    *pA = 10;
    *pB = 5.2;
    *pC = 'U';

    printf( "A = %d\n", a );
    printf( "B = %.2f\n", b );
    printf( "C = %c\n", c );


}