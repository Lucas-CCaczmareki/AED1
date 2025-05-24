#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    char words[4][30] = {
        "step",
        "steps",
        "stripe",
        "stepple"
    };
    int wordsSize = 4;
    char word[50];

    // a lógica tá pronta, mas to copm algum erro no meio disso tudo e eu não sei qual
    strcpy(word, shortestCompletingWord(licensePlate, (char **)words, wordsSize));
    printf( "%s", word );
}


char* licensePlateChars(char* licensePlate) {
    //printf("%s", licensePlate);
    int i;
    int i_aux;

    for( i = 0; licensePlate[i] != '\0'; i++){
        //lp = " 091s3  PS t "
        //0 = 48 e 9 = 57
        //blank = 32

        //Eliminando os espaços (e agora números tbm)
        if( licensePlate[i] == 32 || (licensePlate[i] >= 48 && licensePlate[i] <= 57) ) {
            //agora tem que puxar toda a string dps pra esse espaço
            for( i_aux = i; licensePlate[i_aux] != '\0'; i_aux++ ) {
                licensePlate[i_aux] = licensePlate[i_aux + 1];
            }
            i--; //elimina espaços e números consecutivos
        }

        //Tratando as letras maiúsculas
        //A = 65
        //a = 97
        //Z = 90
        //z = 122
        //anda 32 na ascii pra ir de maiúscula pra minúscula
        
        if( licensePlate[i] >= 65 && licensePlate [i] <= 90 ) {
            //printf("%c", licensePlate[i]);
            licensePlate[i] += 32;
            //printf("%c", licensePlate[i]);
        }

        
    }
    
    //printf("\n%s!", licensePlate);
    //O erro tá na hora de enviar a string
    return licensePlate;
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
    unsigned int tamMenorPalavra = 0;
    int menorPalavra = 0;

    //preciso mandar pro índice segundo a ascii
    // char('a') - 'a' = 0... 
    for( int i = 0; newLicensePlate[i] != '\0'; i++){
        //armazena em ordem alfabética
        n_letterLP[newLicensePlate[i] - 'a'] += 1;
    } 


    int w, l; //word e letter
    for( w = 0; w < wordsSize; w++ ) {
        for( l = 0; words[w][l] != '\0'; l++ ) {
            //percorre cada palavra do array letra por letra
            
            
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
                        w++; //vai pra próxima word
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

                if(sizeof(words[w]) < tamMenorPalavra){
                    tamMenorPalavra = sizeof(words[w]);
                    menorPalavra = w;
                }
            }

        }
    }
    return words[menorPalavra];
}