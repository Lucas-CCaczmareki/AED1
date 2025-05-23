#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool exist(char** board, int boardSize, int* boardColSize, char* word);
bool isAdjacent(char *word, char **board, int l, int c, int w_pos, int boardSize, int* boardColSize, bool **visited);
bool insideLimits(int l, int c, int boardSize, int boardColSize);
bool atLeast2Adj(char **board, int boardSize, int boardColSize, int l, int c, char alvo);


//O Problema tá na hora de transitar do B pro C na tabela, mas sei lá, deu por hoje disso.

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

//OK
bool atLeast2Adj(char **board, int boardSize, int boardColSize, int l, int c, char alvo){
    //vetores de direção
    //0 = cima
    //1 = baixo
    //2 = esquerda
    //3 = direita
    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int count = 0;

    //vai testar com as 4 casas adjacentes
    for (int i = 0; i < 4; i++) {
        //dl[0] e dc[0] = [-1, 0] que é = a board[l+(-1)][c+0]
        int nl = l + dl[i];
        int nc = c + dc[i];

        //se a nossa posição na board existe e é igual o alvo, incrementa count
        if (insideLimits(nl, nc, boardSize, boardColSize) &&
            board[nl][nc] == alvo) {
            count++;
        }
    }

    //se count for maior ou = 2, retorna true
    return count >= 2;
}

//OK? 
bool isAdjacent(char *word, char **board, int l, int c, int w_pos, int boardSize, int* boardColSize, bool** visited){
    //vai ter que tratar caso tenha uma adjacente em duas posições diferentes
    bool f_2adj = false;
    bool f_adjs[4] = {false};
    int i;

    visited[l][c] = true;

     //Se o próximo caracter for \0, significa que chegamos ao final da string com sucesso.
    if(word[w_pos + 1] == '\0'){
        return true;
    }

    //vamo fazer uma função útil pra isso vai
    //verifica se tem pelo menos duas adjacentes válidas
    f_2adj = atLeast2Adj(board, boardSize, *boardColSize, l, c, word[w_pos+1]);
    
    
    if(f_2adj){
        //aqui é pensando no pior caso, as 4 adjacentes são iguais
        //assim, vai executar uma chamada recursiva pra cada adjacente, se todas retornarem falso, voila
        for( i = 0; i < 4; i++){
            //Verifica se a letra seguinte está acima, tratando o final do tabuleiro
            if( i == 0 && l > 0 && word[w_pos + 1] == board[l - 1][c] && !visited[l - 1][c] ) {
                f_adjs[i] = isAdjacent(word, board, l-1, c, w_pos+1, boardSize, boardColSize, visited);
            }

            //Verifica se a letra seguinte está abaixo, tratando o final do tabuleiro (-1 pq l começa em 0)
            if( i == 1 && l < (boardSize-1) && word[w_pos + 1] == board[l + 1][c] && !visited[l + 1][c] ) {
                f_adjs[i] = isAdjacent(word, board, l+1, c, w_pos+1, boardSize, boardColSize, visited);
            }

            //Verifica se a letra seguinte está na esquerda, trata o final do tabuleiro.
            if( i == 2 && c > 0 && word[w_pos + 1] == board[l][c - 1] && !visited[l][c - 1] ) {
                f_adjs[i] = isAdjacent(word, board, l, c-1, w_pos+1, boardSize, boardColSize, visited);
            }
            
            //Verifica se a letra seguinte está na direita, trata o final do tabuleiro.
            if( i == 3 && c < (*boardColSize-1) && word[w_pos + 1] == board[l][c + 1] && !visited[l][c + 1] ) {      
                f_adjs[i] = isAdjacent(word, board, l, c+1, w_pos+1, boardSize, boardColSize, visited);
            }
        }
        //percorre o vetor, se todas forem falsas, não tem palavra válida
        for( i = 0; i < 4; i++){
            if(f_adjs[i]){
                return true;
            }
        }
        //caso a palavra não tenha sido encontrada, eu preciso zerar as posições que eu percorri
        //como é recursivo, isso auqi vai zerando todas chamadas
        visited[l][c] = false;
        return false;
    } else {
        //Verifica se a letra seguinte está acima, tratando o final do tabuleiro
        if(l > 0 && word[w_pos + 1] == board[l - 1][c] && !visited[l - 1][c]  ) {
            if(isAdjacent(word, board, l-1, c, w_pos+1, boardSize, boardColSize, visited)) return true; 
        }

        //Verifica se a letra seguinte está abaixo, tratando o final do tabuleiro (-1 pq l começa em 0)
        if(l < (boardSize-1) && word[w_pos + 1] == board[l + 1][c] && !visited[l + 1][c] ) {
            if(isAdjacent(word, board, l+1, c, w_pos+1, boardSize, boardColSize, visited)) return true;
        }

        //Verifica se a letra seguinte está na esquerda, trata o final do tabuleiro.
        if(c > 0 && word[w_pos + 1] == board[l][c - 1] && !visited[l][c - 1] ) {
            if(isAdjacent(word, board, l, c-1, w_pos+1, boardSize, boardColSize, visited)) return true;
        }
        
        //Verifica se a letra seguinte está na direita, trata o final do tabuleiro.
        //O problema tá aqui, na ocndição de que a próxima não pode ser igual à anterior caso a anterior seja a primeira posição da word.
        if(c < (*boardColSize-1) && word[w_pos + 1] == board[l][c + 1] && !visited[l][c + 1] ) {      
            if(isAdjacent(word, board, l, c+1, w_pos+1, boardSize, boardColSize, visited)) return true;
        }
    }
    
    //Caso não tenhamos encontrado nada nas casas adjacentes, retorna falso.
    //reseta as posições visitadas recursivamente.
    visited[l][c] = false;
    return false;
}


//OK?
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    //dica, esse exercício é mais fácil de resolver com recursão
    int l, c, w_pos = 0, i, j;
    bool isExistent = false;

    //Preciso entender como que isso aqui funcionou direitinho depois.
    //Aloca a matriz de espaços visitados dinâmicamente
    bool** visited = malloc(boardSize * sizeof(bool*));
    for( i = 0; i < boardSize; i++ ) {
        visited[i] = malloc(*boardColSize * sizeof(bool));
    }

    //Inicializa ela em false (nenhum espaço visitado)
    for( i = 0; i < boardSize; i++ ) {
        for( j = 0; j < *boardColSize; j++) {
            visited[i][j] = false;
        }
    }

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
