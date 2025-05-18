#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool exist(char** board, int boardSize, int* boardColSize, char* word);
bool isAdjacent(char *word, char **board, int l, int c, int w_pos, int boardSize, int* boardColSize, bool **visited);
bool insideLimits(int l, int c, int boardSize, int boardColSize);

int main() {
    // Exemplo de tabuleiro
    char *board[] = {
        "ABCE",
        "SFES",
        "ADEE"
    };

    int boardSize = 3;               // número de linhas
    int boardColSize = 4;            // número de colunas por linha (fixo neste exemplo)
    char word[] = "ABCESEEEFS";          // palavra a ser buscada

    bool found = exist(board, boardSize, &boardColSize, word);

    if (found) {
        printf("\nPalavra encontrada!\n");
    } else {
        printf("\nPalavra NAO encontrada.\n");
    }

    return 0;
}

//OK
bool insideLimits(int l, int c, int boardSize, int boardColSize){
    return l >= 0 && l < boardSize && c >= 0 && c < boardColSize;
}

// OK and SIMPLIFIED
bool isAdjacent(char *word, char **board, int l, int c, int w_pos, int boardSize, int* boardColSize, bool** visited) {
    //Matriz de direções adjacentes
    int dl[] = {-1, 1, 0, 0}; //cima e baixo
    int dc[] = {0, 0, -1, 1}; //esquerda e direita
    
    //marca a célula como visitada
    visited[l][c] = true;

    //Se chegar no final da palavra, retorna true;
    if (word[w_pos + 1] == '\0') return true;

    //Isso aqui já implementa a lógica do antigo atLeast2Adj e testa com os 4 adjacentes caso não retorne true no meio
    //isso ocorre por conta as 4 repetições e da matriz de direções. Assim eu garanto que os casos adjacentes válidos são todos testados.
    for(int i = 0; i < 4; i++) {
        //seta as direções para serem analisadas
        int nl = l + dl[i];
        int nc = c + dc[i];

        //Se, está nos limites do tabuleiro E
        //a letra adjacente é igual a próxima da palavra E
        //a casa adjacente analisada não foi visitada nenhuma vez
        if (insideLimits(nl, nc, boardSize, *boardColSize) &&
            board[nl][nc] == word[w_pos + 1] &&
            !visited[nl][nc]) {

                //Caso as chamadas recursivas encontrem a palavra no final, entra no if e retorna true
                if (isAdjacent(word, board, nl, nc, w_pos + 1, boardSize, boardColSize, visited)) {
                    return true;
                }
                //Caso não entre no if, pode ser que esteja em outra casa adjacente, então vai de novo pra dentro do for.
        }
    }
    //Caso não encontre nenhuma casa adjacente...
    //Limpa todas as casas visitadas recursivamente (conforme forem fechando as funções)
    visited[l][c] = false;
    return false;
}

//OK
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    //dica, esse exercício é mais fácil de resolver com recursão
    int l, c, w_pos = 0, i, j;
    bool isExistent = false;

    //Aloca a matriz de espaços visitados dinâmicamente
    //=======================================================

    //Basicamente, cria N ponteiros, e cada ponteiro tem M espaços. N = linhas e M = Colunas
    //Ou seja, cada linha, é um vetor de colunas posições alocado dinâmicamente.

    //Como não podemos alocar dinamicamente e diretamente uma matriz: 
    //Criei n ponteiros para bool. N = Boardsize
    bool** visited = malloc(boardSize * sizeof(bool*));
    //Agora, cada ponteiro pra bool tem 3 n colunas alocadas
    for( i = 0; i < boardSize; i++ ) {
        visited[i] = malloc(*boardColSize * sizeof(bool));
    }

    //Inicializa ela em false (nenhum espaço visitado)
    for( i = 0; i < boardSize; i++ ) {
        for( j = 0; j < *boardColSize; j++) {
            visited[i][j] = false;
        }
    }

    //lembrando, visited[i][j] é uma simplificação bonita pra aritmética de ponteiros
    //*(*(visited + i) + j) = visited[i][j]

    //visited + i       → move i posições no vetor de ponteiros (linhas);
    //*(visited + i)    → pega o ponteiro para a linha i (ou seja, visited[i]);
    //*(visited[i] + j) → move j posições na linha e acessa o valor bool;

    //Resultado: o bool na posição [i][j].


    //=======================================================

    //percorre a matriz na horizontal até encontrar a primeira letra da palavra
    for( l = 0; l < boardSize; l++) { //percorre as linhas
        for( c = 0; c < *boardColSize; c++) { //percorre as colunas
            if( word[w_pos] == board[l][c] ) {
                //retorna se a palavra tá ou não na matriz
                isExistent = isAdjacent(word, board, l, c, w_pos, boardSize, boardColSize, visited);

                //se a palavra já existe retorna ela de uma vez e é us guri
                if(isExistent){
                    return true;
                }
                // aqui eu tenho certeza, preciso zerar a matriz pq saiu da recursão e n achou nada.
                //Inicializa ela em false (nenhum espaço visitado)
                for( i = 0; i < boardSize; i++ ) {
                    for( j = 0; j < *boardColSize; j++) {
                        visited[i][j] = false;
                    }
                }
            }
        }
    }
    //Após a matriz inteira, retorna se existe ou não
    return isExistent;
}
