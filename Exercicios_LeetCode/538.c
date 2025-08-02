#include <stdio.h>
#include <stdlib.h>

// Defina a estrutura do nó da árvore
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int aux_val = 0;

int convertValues(struct TreeNode* root) {
    //Começa na root = 4
    
    //Vai 1o pra direita
    if(root->right != NULL) {
        aux_val += root->right->val;
        root->val += convertValues(root->right);
    }

    //A soma da subarvore direita ta ok, e o aux_val tá com o 30 em teoria pra virar a root, 
    //mas como eu sei (de forma genérica) que ele voltou pra pilha da root inicial?

    //Um contador global? + uma flag

    if(root->left != NULL) {
        aux_val += root->left->val;
        //se ele tem left, da o valor dele pro left e deixa ele fazer a mágica dele
        root->left->val += root->val;
        root->left = convertValues(root->left);
    }
    
    //to numa folha, não altera o valor e volta com o valor dele
    if(root->left == NULL && root->right == NULL) {
        return root->val;
    }

    return root->val; //retorna o valor modificado pras ultimas chamadas

}

struct TreeNode* convertBST(struct TreeNode* root) {
    //Eu quero percorrer a árvore, pra direita tem uma lógica, pra esquerda tem outra
    //A ideia é percorrer pra direita primeiro e já ir modificando os valores
    //Pra quando voltar e ir pra esquerda, somar o valor do pai
    aux_val = root->val;
    convertValues(root);

}












// Funções auxiliares para criar e imprimir a árvore de teste
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
    inorder_traversal(root);
    printf("\n");

    // Chama a sua função convertBST()
    convertBST(root);

    system("pause");

    printf("\nÁrvore convertida (in-order): \n");
    inorder_traversal(root);
    printf("\n");

    return 0;
}