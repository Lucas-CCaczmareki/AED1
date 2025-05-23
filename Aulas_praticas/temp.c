#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

//Declaração das funções

/*
licensePlateChars
retira todos os espaços e números da licensePlate
*/
char* licensePlateChars(char* licensePlate);

/*
shortestCompletingWord

Encontra a menor palavra dentro do array de palavras que contenha os caracteres de letra
dentro de licensePlate.
*/
char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize);

/*
Main
Cria a licensePlate, o words e wordsize.
Chama a função
*/
int main( void ) {
    char licensePlate[50] = {" 091s3  PS t "};
    char *words[] = {
        "step",
        "steps",
        "stripe",
        "stepple"
    };
    int wordsSize = 4;
    char word[50];

    // a lógica tá pronta, mas to copm algum erro no meio disso tudo e eu não sei qual
    strcpy(word, shortestCompletingWord(licensePlate, words, wordsSize));
    printf( "%s", word );
}


char* licensePlateChars(char* licensePlate) {
    int i;
    int j = 0; //conta o índice do result

    //Aparentemente se eu usar a licenseplate ele modifica a string original, então melhor fazer uma cópia
    //no vs tava funcionando, mas tava dando erro no leet

    //Vou mudar um pouco a lógica, vou copiar só os caracteres válidos e/ou convertidos pra dentro de result

    char* result = (char *)malloc((strlen(licensePlate) + 1) * sizeof(char));

    for( i = 0; licensePlate[i] != '\0'; i++){
        //lp = " 091s3  PS t "
        //0 = 48 e 9 = 57
        //blank = 32

        //Eliminando os espaços (e agora números tbm)
        if( licensePlate[i] == 32 || (licensePlate[i] >= 48 && licensePlate[i] <= 57) ) {
            continue; //pula pro próximo loop e ignora
        }

        //Tratando as letras maiúsculas
        //A = 65
        //a = 97
        //Z = 90
        //z = 122
        //anda 32 na ascii pra ir de maiúscula pra minúscula
        
        if( licensePlate[i] >= 65 && licensePlate[i] <= 90 ) {
            //printf("%c", licensePlate[i]);
            result[j] = licensePlate[i] + 32;
            j++;
            //printf("%c", licensePlate[i]);
        }

        //Copiando as minúsculas
        if( licensePlate[i] >= 97 && licensePlate[i] <= 122 ) {
            result[j] = licensePlate[i];
            j++;
        }
    }

    result[j] = '\0';
    return result;
}

/*
- contém todas letras de licensePlate
- ignorar nOs e espaços
- case INsensitive
- se um caracter aparece +1 de uma vez em lP, aparece o mesmo nO de vezes na word
- é garantido ter uma resposta correta.
- se tiver 2 palavras que são a shortest, retorna a 1a
*/
char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize) {
    //preciso arrumar o tamanho aq dps, talvez alocar dinamicamente
    char newLicensePlate[100];
    //printf("%s!", licensePlate); 
    strcpy(newLicensePlate, licensePlateChars(licensePlate));

    //agora eu preciso ver se todas as letras do newLicensePlate estão contidas na palavra do array
    //e depois, ver, das que estão contidas, qual é a menor palavra.

    //pra ver se todas letras tão contidas, eu posso criar um vetor do alfabeto pra license e pra word
    //e ai fazer uma contagem, quantas vezes a letra X aparece em license.
    //Ai se os números diferentes de 0 baterem tá show. Se não, não tá show

    int n_letterLP[26] = {0}; //preenche com 0
    int n_letterW[26] = {0};
    int f_isNotIn = 0;
    unsigned int tamMenorPalavra = INT_MAX;
    int menorPalavra = 0;

    //preciso mandar pro índice segundo a ascii
    // char('a') - 'a' = 0... 
    for( int i = 0; newLicensePlate[i] != '\0'; i++){
        //armazena em ordem alfabética
        n_letterLP[newLicensePlate[i] - 'a'] += 1;
    } 


    //Aqui tá dando um segmentation fault
    int w; //word
    for( w = 0; w < wordsSize; w++ ) {
        //antes de ver quantas vezes cada letra aparece, eu preciso garantir que o vetor esteja zerado
        for( int i = 0; i < 26; i++ ) {
            n_letterW[i] = 0;
        }

        //vou precisar de um vetor com quantas vezes a letra dessa palavra aparece agora
        for( int i = 0; words[w][i] != '\0'; i++){
            //armazena em ordem alfabética
            n_letterW[words[w][i] - 'a'] += 1;
        } 

        //agora eu preciso comparar os 2 vetores e ver se bate
        for( int i = 0; i < 26; i++ ) {
            //os vetores podem ser diferentes,
            //mas as ocorrências de letras do license precisam ser iguais as da word
            if(n_letterLP[i] != 0){ //confere só as letras do license
                if(n_letterLP[i] != n_letterW[i]){ //se isso aqui der diferente a palavra não tá contida
                    f_isNotIn = 1;
                    break;
                }
            }
            //Se ele terminou o for e a palavra tava contida, a flag isNotIn fica desativada
        }
        //meu break precisa vir pra cá (porém ainda não sei como, acho q normal ele já viria pra ca)
        if(f_isNotIn == 0){ //se a palavra estava contida

            //ai eu preciso guardar o tamanho e o índice W de algum jeito
            //pensei em fazer por lógica de menor que a anterior e ai só atualizar o indice
            //se for menor que a última que salvou
            //isso garante que a palavra que fica salva é a primeira menor, como o problema pediu

            if(strlen(words[w]) < tamMenorPalavra){
                tamMenorPalavra = strlen(words[w]);
                menorPalavra = w;
            }
        } else {
            f_isNotIn = 0; //reseta a flag
        }
    }

    return words[menorPalavra];
}