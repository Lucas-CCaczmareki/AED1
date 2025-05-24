#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

//Declaração das funções
char* licensePlateChars(char* licensePlate);
char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize);

//OK
/*
Main
Cria a licensePlate, o words e wordsize.
Chama a função
*/
int main( void ) {
    char licensePlate[50] = {"GrC8950"};
    char *words[] = {
        "measure",
        "other",
        "every",
        "base",
        "according",
        "level","meeting",
        "none",
        "marriage",
        "rest"
    };
    int wordsSize = sizeof(words) / sizeof(words[0]);;
    char word[50];

    // a lógica tá pronta, mas to copm algum erro no meio disso tudo e eu não sei qual
    strcpy(word, shortestCompletingWord(licensePlate, words, wordsSize));
    printf( "%s", word );
}

//OK
/*
licensePlateChars
retira todos os espaços e números da licensePlate
*/
char* licensePlateChars(char* licensePlate) {
    int i;
    int j = 0;              //conta o índice do result
    char* result =          //aloca espaço considerando o pior caso
    (char *)malloc((strlen(licensePlate) + 1) * sizeof(char));

    //Copia apenas caracteres válidos pra result
    for( i = 0; licensePlate[i] != '\0'; i++){
        /* Tabela ASCII:
        0 = 48 e 9 = 57
        blank = 32
        A = 65
        a = 97
        Z = 90
        z = 122
        */

        //Eliminando os espaços e números
        if( licensePlate[i] == 32 || (licensePlate[i] >= 48 && licensePlate[i] <= 57) ) {
            continue;       //pula pro próximo loop e ignora
        }

        //Convertendo e gravando caracteres maiúsculos.
        if( licensePlate[i] >= 65 && licensePlate[i] <= 90 ) {
            result[j] = licensePlate[i] + 32;
            j++;
        }

        //Copiando as letras minúsculas
        if( licensePlate[i] >= 97 && licensePlate[i] <= 122 ) {
            result[j] = licensePlate[i];
            j++;
        }
    }

    result[j] = '\0';       //finaliza a string
    return result;          //retorna licensePlate com caracteres válidos
}

//OK
/*
shortestCompletingWord

Encontra a menor palavra dentro do array de palavras que contenha os caracteres de letra
dentro de licensePlate.
*/
char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize) {
    char newLicensePlate[strlen(licensePlate) + 1];             //aloca segundo o pior caso
    strcpy(newLicensePlate, licensePlateChars(licensePlate));   //copia a string convertida pra dentro da new

    int n_letterLP[26] = {0},       //inicializa em 0
        n_letterW[26] = {0},
        f_isNotIn = 0,
        menorPalavra = 0,
        w = 0;                      //word

    //unsigned pois será usada para comparar com strlen
    //inicializa com o valor máximo pra garantir coerência
    unsigned int tamMenorPalavra = INT_MAX; 

    //OK
    //Registra quantas vezes cada letra do alfabeto apareceu em licensePlate
    for( int i = 0; newLicensePlate[i] != '\0'; i++){
        //armazena em ordem alfabética segundo tabela ASCII
        n_letterLP[newLicensePlate[i] - 'a'] += 1;
    } 

    ///OK
    //Percorre todas as palavras do array words para encontrar a menor
    for( w = 0; w < wordsSize; w++ ) {
        
        //OK
        //Garante que o vetor de contagem de letras sempre comece em 0
        for( int i = 0; i < 26; i++ ) {
            n_letterW[i] = 0;
        }

        //OK
        //Conta quantas vezes cada letra aparece na palavra
        for( int i = 0; words[w][i] != '\0'; i++){
            //armazena em ordem alfabética
            n_letterW[words[w][i] - 'a'] += 1;
        } 

        //OK
        //Compara os 2 vetores de contagem de letra
        for( int i = 0; i < 26; i++ ) {
            //Se todas ocorrências não nulas de letra em license forem iguais as mesmas na word então a palavra ta contida 

            if(n_letterLP[i] != 0){                     //confere apenas as letras que aparecem em license
                if(n_letterLP[i] <= n_letterW[i]){      //se isso aqui der (V) a comparação de letra ta OK
                    f_isNotIn = 0;
                } else {                                //se der falso, ai a W não ta contida
                    f_isNotIn = 1;
                    break;
                }
            }
        }

        //OK
        //Confere se a palavra tá contida
        if(f_isNotIn == 0) { 
            //Se o tamanho da palavra for menor que a última menor ocorrência, então a palavra atual é a menor.
            if(strlen(words[w]) < tamMenorPalavra){
                tamMenorPalavra = strlen(words[w]);     //guarda o tamanho pra comparar
                menorPalavra = w;                       //guarda o índice da menor palavra atual
            }
        } else {
            f_isNotIn = 0;      //reseta a flag pra próxima palavra
        }
    }

    //Retorna a menor palavra encontrada
    return words[menorPalavra];
}