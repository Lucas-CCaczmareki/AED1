/*
Eu preciso dar uma estudada na melhor solução q o chat gpt me mandou, a minha foi bem ineficiente
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows);

int main( void ) {
    //quero só loopar com base no número de rows
    int numRows = 5;
    // 0 1 2 3 4 - 3 2 1 - 0 1 2 3 4 - 3 2 1 - 0 ...
    char s[20] = {"paypalishiring"};
    char s2[20];
    strcpy(s2, convert(s, numRows));
    printf("Old: %s\nNew: %s", s, s2);
}
//com row 5 pra essa palavra, essa é a sequência que eu desejo
//0 1 2 3 4 3 2 1 0 1 2 3 4 3 


/*
char* convert(char* s, int numRows) {

    int i, chr, line = 0, new_chr = 0;
    char new_s[strlen(s)];
    
    //Agora a questão é: Como eu jogo isso pra dentro da string e concateno.
    //não preciso concatenar, eu preciso jogar isso row vezes dentro da string em ordem.
    //i indica a linha q ta indo pra dentro da nova string
    for( i = 0; i < numRows; i++) {
        for( chr = 0; s[chr] != '\0'; chr++ ) { //o i anda só até o final da string

            //printf( "%d ", line ); //o j indica a linha que a letra da string vai entrar.
            if (i == line) {
                new_s[new_chr] = s[chr];
                new_chr++;
            }

            //se a próxima for igual a numRows, chegou na útlima linha
            if( (line + 1) == numRows ){
                //Começa a percorrer ao contrário
                while ( line != 0 ) {
                    line--; //faz ir ao contrário
                    chr++; //ainda anda na palavra

                    //se chegou no final da palavra quebra o looping
                    if (s[chr] == '\0'){ 
                        break;
                    }


                    //printf("%d ", line);
                    if (i == line) {
                        new_s[new_chr] = s[chr];
                        new_chr++;
                    }
                }
            }
            line++; //faz ir na ordem normal
        }
    }
    printf("%s", new_s);
    return new_s; //retorna a string convertida
}
    */


/*
Aplicando algumas sugestões do chat gpt eu acabei usando o código similar ao que ele me deu
ainda mantendo a minha lógica principal.
*/
char* convert(char* s, int numRows) {
    int len = strlen(s);
    //strdup aloca uma nova string que é uma cópia da string passada como argumento;
    //Esses casos cobrem os casos de linha 1, linhas inválidas (> que a palavra) e linhas igual o tamanho da palavra
    if (numRows == 1 || numRows >= len) return strdup(s);

    //aloca dinamicamente uma nova string com o tamanho da antiga +1 pra conter o \0
    char* new_s = (char *)malloc(len + 1 * sizeof(char));
    int new_char = 0;

    //Percorre linha por linha
    //Percorre row vezes, colocando em ordem por linha na nova string. Não é muito eficaz, mas funciona.
    for( int row = 0; row < numRows; row++ ) {
        int pos = 0;
        int down = 1; //direção: 1 = descendo, 0 = subindo
        int current_line = 0;

        //percorre toda string
        while( pos < len ) {
            if( current_line == row ) { //row é a linha q ta entrando na nova string
                new_s[new_char++] = s[pos]; //new_char aqui é incrementado após a atribuição, o contrário seria ++new_char
            }

            //Lógica pra trocar de direção quando chegar num limite (adição do gpt)
            if( current_line == 0 ) {
                down = 1; //recomeça a descer
            } else if( current_line == numRows - 1 ) {
                down = 0; //começa a subir
            }

            //se down for true (1), soma 1 na current line, desce
            //se não, diminui 1 na current line, sobe.
            current_line += down ? 1 : -1;
            pos++; //próxima letra
        }
    }

    new_s[new_char] = '\0'; //finaliza a string
    return new_s;

}   

