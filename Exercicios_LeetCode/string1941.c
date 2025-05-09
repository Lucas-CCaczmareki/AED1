#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool areOccurencesEqual(char* s);
int main ( void ) {
    char s[1000];
    strcpy(s, "vvvvvvvvvvvvvvvvvvv");
    if(areOccurencesEqual(s)) {
        printf("Is good");
    } else {
        printf("Is bad");
    }
}

bool areOccurencesEqual(char* s) {
    int i, lidos[26], fst;
    bool f_good = true , f_primeiro = true;
    char c;

    memset(lidos, 0, sizeof(lidos)); //preenche todos os espaços do vetor com 0
    
    for( i = 0; s[i] != '\0'; i++ ) {
        c = s[i];
        //considerando a tabela ascci, isso aqui faz com que ordenemos a quantidade de vezes que as letras aparecem
        //de a - z no vetor.
        lidos[c - 'a']++;
    }

    for( i = 0; i < 26; i++){
        //a flag só é verdadeira, caso todos números dentro de lido sejam iguais (exceto zeros)
        if( lidos[i] != 0  && f_primeiro ) {
            f_primeiro = false;
            fst = lidos[i];
        }
        if( lidos[i] != 0 && lidos[i] != fst ) {
            f_good = false;
        }
    }
    
    return f_good;
}