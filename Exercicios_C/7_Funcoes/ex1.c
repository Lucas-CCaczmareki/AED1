#include <stdio.h>

/*
=========================================
Main
1. Crie uma func¸ao que recebe como par ˜ ametro um n ˆ umero inteiro e devolve o seu dobro.
=========================================
*/

float DoubleValue( float n );

int main( void ) {
    int a, twoA;

    printf( "Type a number for A and I'll double it: " );
    scanf( "%d", &a );
    twoA = DoubleValue(a);
    printf( "The value is: %d", twoA );
}

float DoubleValue ( float n ) {
    return n*2;
}