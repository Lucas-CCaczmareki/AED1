#include <stdio.h>

/*
==================================
Main
1. Fac¸a um programa que entao leia uma string e a imprima. 
==================================
*/

int main( void ){
    char str[30];

    printf( "Type a string: " );
    fgets( str, 30, stdin );
    printf( "You typed: %s", str );
}