#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
Percorre a árvore em ordem reversa (direita, raiz, esquerda)
Acumula a soma dos valores maiores

*/
void reverseInOrderTraversal(struct TreeNode* node, int* cumulative_sum) {
    //Se o nó for nulo, faz nada
    if (node == NULL) {
        return;
    }

    //Visita a subárvore direita primeiro
    //A recursão vai até o nó mais a direita
    reverseInOrderTraversal(node->right, cumulative_sum);

    //Processa o nó atual (a Raiz do percurso)
    //A variável cumulative_sum agora tem a soma de todos os nós que são maiores que o atual
    *cumulative_sum += node->val;
    node->val = *cumulative_sum;
    
    //Visita a subárvore esquerda
    //A soma acumulada já inclui o valor da raiz atual e de toda subárvore direita
    reverseInOrderTraversal(node->left, cumulative_sum);
}

/*
Função que converte a BST pra "Greater Tree"
*/

struct TreeNode* convertBST(struct TreeNode* root) {
    //Inicializa a soma acumulada com 0;
    int sum = 0;

    //Chama a função auxiliar que faz o trabalho de verdade
    reverseInOrderTraversal(root, &sum);

    // Retorna a raiz da árvore que já teve os valores modificados
    return root;
}

/*
A partir daqui são só as funções pra teste
*/


// --- Funções auxiliares para teste (iguais às suas) ---
struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void inorder_traversal(struct TreeNode* node) {
    if (node == NULL) {
        return;
    }
    inorder_traversal(node->left);
    printf("%d ", node->val);
    inorder_traversal(node->right);
}

// --- Função principal para testar o seu código ---
int main() {
    // Criando a árvore de exemplo: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    struct TreeNode* root = newTreeNode(4);
    root->left = newTreeNode(1);
    root->right = newTreeNode(6);
    root->left->left = newTreeNode(0);
    root->left->right = newTreeNode(2);
    root->left->right->right = newTreeNode(3);
    root->right->left = newTreeNode(5);
    root->right->right = newTreeNode(7);
    root->right->right->right = newTreeNode(8);

    printf("Árvore original (in-order): \n");
    inorder_traversal(root); // Saída: 0 1 2 3 4 5 6 7 8
    printf("\n\n");

    // Chama a função convertBST()
    convertBST(root);

    printf("Árvore convertida (in-order): \n");
    inorder_traversal(root); // Saída esperada: 36 36 35 33 30 26 21 15 8
    printf("\n");

    system("pause");

    return 0;
}
