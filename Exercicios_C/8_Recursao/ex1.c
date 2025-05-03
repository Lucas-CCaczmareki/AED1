#include <stdio.h>

/*
==============================================
Main
1. Crie uma func¸ao recursiva que receba um n ˜ umero inteiro positivo N e calcule o somat ´ orio ´
dos numeros de 1 a N.
==============================================
*/

int SumTilN( int n );

int main( void ) {
    int n, sumN;    printf( "Choose a number: " );
    scanf( "%d", &n );
    sumN = SumTilN( n );

    printf( "The sum from 1 until %d is: %d", n, sumN );
}

/*
==============================================
SumTilN
Essa é uma função recursiva para somar de n até 1 e funciona da seguinte maneira
Suponha n = 5:
ela retorna n + elaMesma(n - 1) == 5 + elaMesma(4)
    dentro dela, ela se chama novamente com 4 + elaMesma(3)
    e faz isso de novo até chegar em:
        2 + elaMesma(1) -> elaMesma(1) retornará 1.
então, quando ela para de se chamar, ela volta ao seu primeiro return n(5) + chamadaRecursiva(4, 3, 2 e 1)

PS: Aqui eu precisei usar o chat gpt pra revisar o conceito de chamada recursiva, que foi só apresentado
mas nunca foi praticado em PC.
==============================================
*/
int SumTilN( int n ) {
    if ( n == 1 ) {
        return 1;
    } else {
        return n + SumTilN( n - 1 );
    }
}