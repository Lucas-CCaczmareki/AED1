#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//Função recursive que verifica a altura e o balanceamento simultaneamente
//Essa função retorna a altura do nó se estiver balanceada (else da debaixo)
//Ou retorna -1 se tiver algum desbalanceamento. (ou seja, abs(alt_esq - alt_dir) > 1) e ai propaga esse -1 pra cima pq fodase a altura


int height(struct TreeNode* root){
    int alt_esq = 0,
        alt_dir = 0;

    //Trata o caso especial de árvore vazia
    if(root == NULL) {
        return 0;
    }

    //Trata o caso especial de só ter a raiz
    if(root->left == NULL && root->right == NULL) {
        return 1;
    //Trata os outros casos?
    } else if (root->left == NULL && root->right != NULL) {
        alt_esq = 0;
        alt_dir = height(root->right);
        if(alt_dir == -1){
            return -1;
        }
    } else if (root->left != NULL && root->right == NULL) {
        alt_esq = height(root->left);
        if(alt_esq == -1) {
            return -1;
        }
        alt_dir = 0;
    } else {
        alt_esq = height(root->left);
        if(alt_esq == -1) {
            return -1; //propaga o -1
        }
        
        alt_dir = height(root->right);
        if(alt_dir == -1) {
            return -1; //propaga o -1
        }
    }
    
    if(abs(alt_esq - alt_dir) > 1) { //ta desbalanceada
        return -1;
    } else { //ta balanceada
        //Esse ternário aqui retorna 1 + a maior altura. Pra retornar a altura da árvore ou subarvore
        return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
    }
}

//Essa função só diz se a nossa árvore tá balanceada ou não.
bool isBalanced(struct TreeNode* root) {
    int balanced = 0;
    balanced = height(root);

    if(balanced == -1) {
        return false;
    }
    
    return true;
}
