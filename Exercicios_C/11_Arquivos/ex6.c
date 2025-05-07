#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
================================================
Main
6. Fac¸a um programa que receba do usuario um arquivo texto e mostre na tela quantas ´
vezes cada letra do alfabeto aparece dentro do arquivo.
================================================
*/

//BRAINSTORM
/*
A chave do problema aqui tá em incrementar a posição correta do vetor de letras do alfabeto
Pra definir o índice, (peguei a ideia do gpt) posso usar a tabela ascii como base, afinal o C faz
a conversão automática, por exemplo, 'a' == 97;

então posso fazer algo do tipo:
letras[c - 'a'];
assim, caso c = 'a', a posição do vetor seria 0, se fosse b seria 1, e assim vai.

porém, preciso converter todos caracteres em maiúsculo para minúsculo, e conferir se são caracteres.
*/

int main ( void ) {
    FILE* fp = fopen("line.txt", "r");
    int letras[26] = {0}, i; //isso preenche todo o vetor com 0 automaticamente
    char c, j = 97;

    //supondo que o arquivo só teria caracteres
    while( ( c = fgetc(fp) ) != EOF ) {
        //pra converter uma letra maiúscula pra minúscula com base na tabela ASCII
        //precisa somar 32 ao valor da letra
        //porém só podemos fazer isso se a letra estiver entre 97 e 122

        //essa letra GARANTE que só os caracteres alfabeticos serão lidos.
            //ou seja, podemos fazer esse programa com um arquivo de texto e frases.
            //porém, caracteres acentuados não serão considerados.
        if(isalpha(c)) { 
            if ( c >= 97 && c <= 122); else {
                c += 32; //converte uma letra maiúscula pra minúscula
            }
            //PS da pra fazer isso tudo muito mais fácil com a ctype.h
            letras[c - 'a']++;
        }
    }

    for( i = 0; i < 26; i++ ) {
        printf( "letras[%c] = %d\n",j, letras[i] );
        j++;
    }
    return 0;
}