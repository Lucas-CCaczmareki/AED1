#include <stdio.h>
#include <stdlib.h>

//Função recursiva para calcular o fatorial de um número
long long fat(int n) {
    if(n == 0) {
        return 1;
    } else {
        return n * fat(n-1);
    }
}

long long dfs(int* nums, int numsSize) {
    //retorna 1, pois com 3 nodos só tem uma possibilidade correta além da padrão.
    if(numsSize < 3) {
        return 1;           
    }
    
    int root = nums[0];     //1a posição é sempre fixa

    //Cria 2 vetores com o tamanho de numsSize pra facilitar a minha vida por enquanto
    int *left_nodes = (int*)malloc(sizeof(int) * numsSize);
    int *right_nodes = (int*)malloc(sizeof(int) * numsSize);

    //contadores de índice pro vetor left e right
    int l = 0, r = 0; 

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
    //OK agora eu tenho 2 vetores com a ordem relativa (filhos não podem aparecer antes dos pais) preservada!

    //E agora eu tenho X maneiras de escolher L(ou R) posições entre as numsSize-1 livres
        //PS, ao escolher L posições, as que sobrarem são preenchidas pelo R.
    
    //X é dado pela Combinação, C(numSize-1, L) ou C(numsSize-1, R). 
        //Pois como numsSize-1 = L + R, a simetria da formula da combinação é mantida

    long long C = (fat(numsSize - 1)) / (fat(l)*(numsSize - 1 - l)); //Calcula a formula da combinação pra esquerda


    return C * dfs(right_nodes, r) * dfs(left_nodes, l);
}

int numOfWays(int* nums, int numsSize) {
    long long result = dfs(nums, numsSize) - 1;
    return result;
}

int main() {
    int nums1[] = {2, 1, 3};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);

    int nums2[] = {3, 1, 2, 5, 4, 6};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);

    printf("Test Case 1 (nums = {2, 1, 3}):\n");
    printf("Expected result: 1\n");
    printf("Your result: %d\n", numOfWays(nums1, size1));

    printf("\nTest Case 2 (nums = {3, 1, 2, 5, 4, 6}):\n");
    printf("Expected result: 5\n");
    printf("Your result: %d\n", numOfWays(nums2, size2));

    system("pause");

    return 0;
}