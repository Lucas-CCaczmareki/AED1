#include <stdio.h>
#include <stdlib.h>

#define MAX 1001        //o máximo que o problema indicou
#define MOD 1000000007  // o módulo que o problema indicou

//Cria a matriz que vai ter nosso lindíssimo triangulo de pascal
long long comb[MAX][MAX];

void buildPascal() {
    for (int n = 0; n < MAX; n++) {
        comb[n][0] = 1; //todo No nC0 = 1 por definição
        for(int k = 1; k <= n; k++) {
            //Armazena em módulo pra não estourar
            comb[n][k] = (comb[n-1][k-1] + comb[n-1][k]) % MOD;
        }
    }
}

long long dfs(long long* nums, int numsSize) {
    //retorna 1, pois com 3 nodos só tem uma possibilidade correta além da padrão.
    if(numsSize < 3) {
        return 1;           
    }
    
    long long root = nums[0];     //1a posição é sempre fixa
    //contadores de índice pro vetor left e right
    int l, r;

    //Cria 2 vetores com o tamanho de numsSize pra facilitar a minha vida por enquanto
    long long *left_nodes = (long long*)malloc(sizeof(long long) * numsSize);
    long long *right_nodes = (long long*)malloc(sizeof(long long) * numsSize);

    
    l = r = 0;
    //Percorre o vetor, formando as subarvores mantendo a ordem RELATIVA
    for(int i = 1; i < numsSize; i++) {
        if(nums[i] > root) { 
            //Se for maior que a root, faz parte do right nodes (subarvore da direita)
            right_nodes[r] = nums[i];
            r++;
        } else { 
            //Se for menor, faz parte dos left nodes (subarv da esquerda)
            left_nodes[l] = nums[i];
            l++;
        }
    }   

    //Calcula de quantas maneiras podemos organizar a subarvore esquerda no espaço que sobrou
    //Como a formula da combinação é simétrica pra direita funciona igual.
    long long C = comb[numsSize-1][l];

    //Calcula de quantas formas podemos organizar as subarvores das subarvores
    long long left = dfs(left_nodes, l);
    long long right = dfs(right_nodes, r);

    //Multiplica os resultados em modulo pra não estourar o long long
    long long result = (((C * left)%MOD) * right) % MOD;

    //Libera a memória ao final da recursão
    free(left_nodes);
    free(right_nodes);

    return result;
}

int numOfWays(int* nums, int numsSize) {
    //Cria o triangulo de pascal para não usar o fatorial da combinação
    buildPascal();

    //Copia o vetor n para outro com formato long long e não dar problema de atribuição
    long long *longNums = malloc(sizeof(long long) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        longNums[i] = nums[i];
    }

    //Retorna o resultado liberando a memória (-1 desconsiderando o vetor dado pelo exercício)
    long long result = dfs(longNums, numsSize) - 1;
    free(longNums);
    return result;
}

//Main com alguns vetores para teste
int main() {
    int test1[] = {2, 1, 3};
    int test2[] = {3, 4, 5, 1, 2};
    int test3[] = {1, 2, 3};
    int test4[] = {3, 1, 2, 5, 4, 6};

    printf("Teste 1: %d\n", numOfWays(test1, sizeof(test1) / sizeof(int))); // Esperado: 1
    printf("Teste 2: %d\n", numOfWays(test2, sizeof(test2) / sizeof(int))); // Esperado: 5
    printf("Teste 3: %d\n", numOfWays(test3, sizeof(test3) / sizeof(int))); // Esperado: 0
    printf("Teste 4: %d\n", numOfWays(test4, sizeof(test4) / sizeof(int))); // Esperado: 19

    //system("pause");

    return 0;
}