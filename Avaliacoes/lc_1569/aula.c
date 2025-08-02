int dfs(int* nums, int numsSize) {
    if(numsSize < 3) {
        return 1; //retorna 1, pois com 3 nodos só tem uma possibilidade correta além da padrão.
    }

    int root = nums[0];

    //Cria 2 vetores com o tamanho de numsSize pra facilitar a minha vida por enquanto
    int *left_nodes = (int*)malloc(sizeof(int) * numsSize);
    int *right_nodes = (int*)malloc(sizeof(int) * numsSize);

    int l = 0, r = 0; //contadores de índice pro vetor left e right

    for(int i = 1; i < numsSize; i++) {
        //Se for maior que a root, faz parte do right nodes
        //Se for menor, faz parte dos left nodes
        if(nums[i] > root) {
            right_nodes[r] = nums[i];
            r++;
        } else {
            left_nodes[l] = nums[i];
            l++;
        }
    }
    //Agora com base nesses 2 vetores eu sei que eles podem se permutar entre si mas não podem mudar
    //suas ordens individuais. Respeitando a condição de um filho nunca aparece antes do pai pra
        //formar a mesma árvore.

    //Ai vem a parte que eu não saquei que é os lance matemáticos pra calcula a Combinação de K até N
    //Cleft/m-1 -> sendo m o tamanho do array (-1 por causa da root que é fixa)

    int P = (fat(numsSize - 1)) / (fat(l)*(numsSize - 1 - l));


        //Pelo que eu entendi, essa fórmula vai me retornar o valor de quantas posições válidas possíveis a subárvore consegue assumir com base no tamanho do vetor. E ai qualquer subárvore formada a partir da raiz (índice 0 do vetor) vai assumir essa combinação possível.
        //No final é só multiplicar todas as combinaçãoes, mas tipo, como?

    //return dfs(left_nodes, numsSize) * dfs(right_nodes) *

    //return 0; //provisorio
}

int numOfWays(int* nums, int numsSize) {
    
}