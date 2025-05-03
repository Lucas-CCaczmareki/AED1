/*
1. Fac¸a um programa que determine o mostre os cinco primeiros multiplos de 3, conside- ´
rando numeros maiores que 0
*/

#include <stdio.h>

int main(){
    int i;

    for ( i = 1; i < 6; i++ ) {
        printf( "3 x %d = %d\n", i, i * 3 );
    }
}