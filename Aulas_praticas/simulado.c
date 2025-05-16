#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool isAdjacent(char *word, char **board, int l, int c, int w_pos, int boardSize, int* boardColSize){
    bool f_isAdj = false;
    //supondo a posição [1][0]
    //vai ter que ver se i-1 e i+1 são as letras
    //vai ter que ver se j-1 e j+1 são as letras
    //vai ter que tratar caso tenha uma adjacente em duas posições diferentes

    //printf("%s", word);
    //printf("\n%c", board[0][1]);

    printf("%c", word[w_pos+1]);
    printf("%c", board[l][c+1]);

    //Enquanto a posição anterior a posição recebida não for \0 (não ta no final da string)
    //Como eu identifico que é adjacente?
    while( true ){ //isso tudo aqui ainda não tá tratando casos de letras repetidas
        if(l != 0 && word[w_pos + 1] == board[l - 1][c] ) {
            isAdjacent(word, board, l-1, c, w_pos++, boardSize, boardColSize);

        } else if(l != boardSize && word[w_pos + 1] == board[l + 1][c] ) {
            printf("entrei");
            isAdjacent(word, board, l+1, c, w_pos++, boardSize, boardColSize);

        } else if(c != 0 && word[w_pos + 1] == board[l][c - 1] ) {
            isAdjacent(word, board, l, c-1, w_pos++, boardSize, boardColSize);

        } else if(c != *boardColSize && word[w_pos + 1] == board[l][c + 1] ) {
            

            //é a run do b que tá dando merda
            
            //o problema tá no l e no c que eu to enviando na chamada recursiva
            isAdjacent(word, board, l, c+1, w_pos++, boardSize, boardColSize);

        } else {
            //supondo q tudo deu certo e ele só entra aqui no último loop
            //ou caso não encontre uma adjacente
            //eu preciso fazer a lógica de return.
            if(word[w_pos + 1] == '\0'){
                return true;
            } else {
                return false;
            }
        }
    }
    //retorna a posição da letra adjacente
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    //recebe a board mas pq ela é um ponteiro pra ponteiro?
    //boardSize? n linhas?
    //boardColSize? m colunas? mas pq é um ponteiro?
    //recebe a palavra

    //dica, esse exercício é mais fácil de resolver com recursão

    int l, c, w_pos = 0;

    //printf("%s", word);
    //printf("\n%c", board[0][1]);

    //percorre a matriz na horizontal,
    for( l = 0; l < boardSize; l++) { //percorre as linhas
        for( c = 0; c < *boardColSize; c++) { //percorre as colunas
            if( word[w_pos] == board[l][c] ) {
                //retorna se a palavra tá ou não na matriz
                return isAdjacent(word, board, l, c, w_pos, boardSize, boardColSize);
                //agora eu preciso testar se as adjacentes fazem parte da palavra
                //e depois se essa que faz parte, tem uma adjacente que faz parte.
            }
        }
    }
    return false;
}
