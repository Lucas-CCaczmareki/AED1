#include <stdio.h>
#include <stdlib.h>

int maxArea(int *height, int heighSize);
/*
Main
This programs aims to solve the eleventh problem from leetcode
It searches an array of lines and calculates the bigger rectangle made from 2 of them.

This rectangle is called a container
*/

int main ( void ) {
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int heightSize = 9;
    int biggestArea = maxArea(height, heightSize);
}

/*
maxArea
This function discover which is the biggest container and
return the amount of water that it can contain.
*/

int maxArea(int *height, int heightSize) {
    //height contém a altura em Y da linha
    //o índice (0, 1, 2...) que essa altura está é onde essa linha encontra o x
    //heightSize é o tamanho do vetor

    //O que eu quero e o que eu PRECISO
        //Eu poderia querer as 2 maiores retas e calcular com base nisso
        //Porém, eu só preciso da área. não de quais retas foram usadas pra calcular essa área ou whatever.
    int i, j;
    int max = 0;
    int area = 0;
    int lowestHigh = 0;
    int distance = 0;

    //Eu vou ter que alocar um vetor dinâmicamente com base no máximo de possibilidades;
    //Então, se eu tenho n retas, eu quero a combinação de todas com todas
    //na real eu só preciso se eu quiser guardar as outras áreas.

    for( i = 0; i < heightSize; i++ ) {
        for( j = 0; j < heightSize; j++) {
            if( i != j ){ //ou seja, a princípio n vale duas linhas no mesmo x

                //Calcula a distância entre as linhas (valor da base)
                if( i > j ) {
                    distance = i-j;
                } else {
                    distance = j-i;
                }
                
                //limita a altura do recipiente pela altura da menor linha
                if( height[i] < height[j] ) {
                    lowestHigh = height[i];
                } else {
                    lowestHigh = height[j];
                }

                area = lowestHigh * distance;
                
                if ( area > max ) {
                    max = area;
                }
            }
        }
    }
    return max;
}