/*
1. Fac¸a um programa que receba dois numeros e mostre qual deles ´ e o maior

PS to digitando em inglês pra não me incomodar com acentuação bugando no terminal 
*/

#include <stdio.h>

int main(){
    int a, b;
    printf( "Type a number for a: " );
    scanf( "%d", &a );
    printf( "Type a number for b: " );
    scanf( "%d", &b );

    if ( a > b ) {
        printf( "A is greater than B" );
    } else {
        printf( "B is greater than A" );
    }
    return 0;
}