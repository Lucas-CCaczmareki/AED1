/*
Revisando o padrão de alocação dinâmica pra prática de hoje.
*/

int main( void ) {
    //=======================================================
    //Básicão (variaveis e afins)
    //=======================================================
    int* n = (int *)malloc(sizeof(int));

    *n = 6;         //acessa igual ponteiros, pq malloc retorna um ponteiro pro tipo do casting
    //free(n);      //boa prática liberara  memória depois de usar


    //=======================================================
    //Alocar vetor dinamicamente
    //=======================================================
    //Alocar vetores dinamicamente é útil pois nos permite decidir o tamanho dele em tempo de execução (e mudar também)
    //Eles também continuam existindo, mesmo fora do escopo da função até você dar free();
    int *vetor = (int *)malloc(sizeof(int) * *n);

    //o acesso a vetor estático ou dinâmico é igual em C
    vetor[2] = *n;  //vetor[2] = *(vetor + 2), ou seja, é igual mover o ponteiro;


    //=======================================================
    //Alocar matriz dinamicamente
    //Vetor de ponteiros:
    //=======================================================
    int linhas = 3, colunas = 4;

    //Cria um espaço na memória que vai armazenar ponteiros pra ponteiros int, cada espaço vai ter 1 ponteiro int.
    // O número de espaço é definido pelas linhas
    int **matriz = (int **)malloc(linhas * sizeof(int *));

    for( int i = 0; i < linhas; i++ ) {
        //Cada ponteiro (linha da matriz) vai ter um vetor de ints associado. 
        // O tamanho desse vetor é definido pelas colunas
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }

    matriz[1][2] = *n; //usa igual uma matriz estática pela propriedade padrão do C

    for( int i = 0; i < linhas; i++ ) {
        free(matriz[i]); //libera cada linha
    }
    free(matriz);

    //=======================================================
    //Alocar matriz dinamicamente
    //Bloco contínuo
    //=======================================================
    //Dessa maneira, armazenamos toda a matriz como se fosse um grande vetorzão na memória
    int *dados = (int *)malloc(linhas * colunas * sizeof(int));

    //Cria um vetor de ponteiros de tamanho linhas(que nesse caso é 3)
    int **matriz = (int **)malloc(linhas * sizeof(int *));

    for( int i = 0; i < linhas; i++ ) {
        //dados é um ponteiro pro início do nosso bloco que guarda a matriz como um vetor
        //matriz é nosso vetor de ponteiros do tamanho das linhas
        //matriz[i] é o ponteiro do vetor que aponta pra linha i

        //O resto é uma aritmética de ponteiros
            //dados é um ponteiro pro início da matriz vetorizada linearmente
            //colunas indica o "passo" pra chegar na próxima linha.
                //Se colunas igual a 4, então o primeiro elemento da próxima linha tá 4 posições à frente
            //i indica a linha, e nesse caso, diz pra dados, quantas posições andar com base em colunas, que é o passo
            //então se i = 1; a linha 1 da matriz começa em dados[i*colunas] que é = dados[1*4] nesse caso. 
        matriz[i] = dados + i * colunas;
    }



    //Lista encadeada?



    return 0;
}

