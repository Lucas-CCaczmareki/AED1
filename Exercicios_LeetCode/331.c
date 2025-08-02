#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isValidSerialization(char* preorder);

int main() {
    char *preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#";
    if(isValidSerialization(preorder)) {
        printf("Ta correto meu nobre\n");
    } else {
        printf("Nao ta correto meu querido\n");
    }
    system("pause");
}

bool isValidSerialization(char* preorder) {
    int slots = 1;

    //tratando o caso especial de string vazia
    if(preorder == NULL) {
        return true;
    }

    //Tratando caso especial de árvore vazia e raiz vazia
    if(preorder[0] == '#') {
        if(strlen(preorder) > 1)  {
            return false;
        } else {
            return true;
        }
    }

    //A lógica ta pronta, a dica de slots foi muito certeira
    

    for (int i = 0; preorder[i] != '\0'; i++) {
        if (slots == 0) {
            //vem aqui em cima pra evitar conflitar quando ele zerar por que acabou
            return false; //se zerou e o loop não terminou quer dizer que deu ruim na ordem
        }

        if(preorder[i] != ',') {

            if(preorder[i] == '#') {
                slots -= 1;
            } else {
                //O único problema com o programa é que ele não identifica números com múltiplos dígitos, tipo 100 e 92
                //Ai eu preciso tratar ele aqui possivelmente

                slots = slots - 1 + 2; //consome 1 slot, cria 2

                //A solução fácil é ele andar até a próxima vírgula ou \0
                while (preorder[i] != ',' && preorder[i] != '\0') {
                    i++;
                }
                if (preorder[i] == '\0') { // pra evitar o buffer overflow
                    break;
                }
            }   
        }
    }

    if (slots == 0) {
        return true;
    } else {
        return false;
    }

}
