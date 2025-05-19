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

    printf("%d", biggestArea);
}

/*
maxArea
This function discover which is the biggest container and
return the amount of water that it can contain.
*/

int maxArea(int *height, int heightSize) {
    //Aparentemente a estratégia do Roa aqui n funciona, eu n posso exceder o tempo limite de execução
    //Aparentemente não importa que seja a maior reta, ela pode ser pequena e ainda assim gerar o maior container
        //Fazer tudo de novo, posso seguir a estratégia do gpt ou tentar pensar em algo.

    //a lógica aqui é usar o left e o right pra ir movendo o right até o left, garantindo sempre a maior base possível (1 variável)
    //e ir testando com todas retas. É mais simples do que confiar em 2 variáveis.


    int left = 0, right = heightSize - 1; //começa no priemeiro e último índice respectivamente
    int max = 0;

    while (left < right) {
        //uso do ternário, se a condição for V, executa antes dos ":", se for F, executa depois.
        int h = height[left] < height[right] ? height[left] : height[right];
        int w = right - left; // base = distância entre os índices
        int area = h * w; // area = base * altura

        if( area > max ) max = area;

        //agora que vem o pulo do gato, o movimento dos ponteiros:
        //ao mover o ponteiro, devemos movê-lo com base na menor altura (o que aponta pra menor reta se move);
        //por que isso? por que se movessemos o maior, matemáticamente só seria possível manter ou diminuir a área (confia, dá certo)
        //portanto movemos o outro, e eliminamos metade das possibilidades de repetição inútil.

        if( height[left] < height[right] ) {
            left++;
        } else {
            right--;
        }

    }
    return max;
}