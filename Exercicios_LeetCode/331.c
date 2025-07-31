#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    char *preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#";
    if(isValidSerialization(preorder)) {
        printf("Ta correto meu nobre");
    } else {
        printf("Nao ta correto meu querido");
    }
}

bool isValidSerialization(char* preorder) {
    int slots = 1;

    //tratando o caso especial de string vazia
    if(preorder[0] == NULL) {
        return true;
    }

    for (int i = 0; i != '\0'; i++) {
        if(preorder[i] != ',') {
            if(preorder[i] == '#') {
                slots -= 1;
            } else {
                slots = slots - 1 + 2; //consome 1 slot, cria 2
            }   
        }
    }

    if (slots == 0) {
        return true;
    } else {
        return false;
    }

}
