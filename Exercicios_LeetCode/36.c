/*
This programs determines if a 9x9 sudoku board is valid by validating ONLY the filled cells

1. Each row must contain the digits 1-9 without repetition
2. Each column must contain the digits 1-9 without repetition
3. Each of the nine 3x3 sub boxes of the grid must contain the digits 1-9 without repetition

Note: 
-The board can be valid but not necessarily solvable
-Validate only the filled cells
-The unfilled spaces are filled with a dot: "."

Constraints:
-board.length == 9
-board[i].length == 9
-board[i][j] is a digit 1-9 or '.'.

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidSudoku  (char** board, int boardSize, int* boardColSize);
bool isValidBoxes   (char** board);
bool isValidLines   (char** board);
bool isValidColumns (char** board);

/*
Main
Creates the board and calls the function
*/
int main() {
    int boardSize = 9;
    int* boardColSize = malloc(boardSize * sizeof(int));
    char** board = malloc(boardSize * sizeof(char*));

    // Sample 9x9 board (can modify as needed)
    char tempBoard[9][9] = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };



    for (int i = 0; i < boardSize; i++) {
        board[i] = malloc(9 * sizeof(char));
        boardColSize[i] = 9;
        for (int j = 0; j < 9; j++) {
            board[i][j] = tempBoard[i][j];
        }
    }

    // Call your function
    bool result = isValidSudoku(board, boardSize, boardColSize);
    printf("Result: %s\n", result ? "true" : "false");

    // Free memory
    for (int i = 0; i < boardSize; i++) {
        free(board[i]);
    }
    free(board);
    free(boardColSize);

    return 0;
}

//Se if the lines are valid
bool isValidLines(char** board){
    bool lines = true;
    int line, i, j;

    //Compares each one with everyone
    for( line = 0; line < 9; line++){
        for( i = 0; i < 9; i++ ) {
            if( board[line][i] != '.') { //if its not a blank space
                for( j = i; j < 9; j++ ) {
                    //See if theres a repeated number
                    if( i != j && board[line][i] == board[line][j] ) {
                        lines = false;
                        return lines;
                    }
                }
            }
        } 
    }
    return lines;
}

//See if the columns are valid
bool isValidColumns(char** board){
    bool columns = true;
    int column, i, j;

    for( column = 0; column < 9; column++ ) {
        for( i = 0; i < 9; i++ ) {
            if( board[i][column] != '.' ) {
                for( j = i; j < 9; j++ ) {
                    //See if there's a repeated number on the column
                    if( i != j && board[i][column] == board[j][column] ) {
                        columns = false;
                        return columns;
                    }
                }
            }
        }
    }
    return columns;
}

//See if the boxes are valid
bool isValidBoxes(char** board){
    bool boxes = true;
    int boxLimit[2] = {0, 2}; //superior line and inferior column
    int i, j, k;

    //aqui eu admito, é interessante botar um backtracking
    int num[9] = {0};

    //Go through the boxes
    for( boxLimit[0] = 0; boxLimit[0] < 9; boxLimit[0] += 3 ) {
        for( boxLimit[1] = 2; boxLimit[1] < 9; boxLimit[1] += 3 ) {
            //Percorre a box certinho se Deus quiser
            //Reseta o vetor de números na box sempre que mudar de box
            for( k = 0; k < 9; k++ ) {
                num[k] = 0;
            }

            for( i = boxLimit[0]; i < boxLimit[0] + 3; i++ ) {
                for( j = (boxLimit[1] - 2); j <= boxLimit[1]; j++ ) {
                    if( board[i][j] != '.') {
                        int idx = board[i][j] - '1'; //transforma '1' em '0' e joga pro indice
                        if(idx < 0 || idx > 8) return false; //se deu a louca no sudoku
                        
                        if( num[idx] == 1 ) { //ou seja, se esse número já apareceu
                            boxes = false;
                            return boxes;
                        }

                        num[idx] = 1;
                    }
                }
            }
        }
    }

    /*
    //Go through the boxes
    for( boxLimit[0] = 0; boxLimit[0] < 9; boxLimit[0] += 3 ) {
        for( boxLimit[1] = 2; boxLimit[1] < 9; boxLimit[1] += 3 ) {
            //Compares each number with every from the box
            //Criando o primeiro ponteiro pra pecorrer a caixa
            for( i = boxLimit[0]; i < boxLimit[0] + 3; i++ ) {
                for( j = (boxLimit[1] - 2); j <= boxLimit[1]; j++ ) {
                    if( board[i][j] != '.' ) {
                        //Aqui que tá o problema
                        for( l = i; l < boxLimit[0] + 3; l++ ) {
                            for( c = j; c <= boxLimit[1]; c++) {
                                if( board[l][c] != '.' ) {
                                    if( !( i == l && j == c ) && board[i][j] == board[l][c] ) {
                                        boxes = false;
                                        return boxes;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    */
    return boxes;

}



//See if all options are valid and returns
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    bool lines = isValidLines(board);
    bool columns = isValidColumns(board);
    bool boxes = isValidBoxes(board);

    return lines && columns && boxes;
}