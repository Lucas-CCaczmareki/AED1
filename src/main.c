#include <stdio.h>
#include <stdlib.h>
// Binary tree preorder traversal
// Given the root of a binary tree, return the preorder traversal (an array of the values in preorder) of its nodes values


//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void fillArray(struct TreeNode* root, int** preOrderArray, int* capacity, int* current_size) {
    if(*current_size == 0) {
        if(root != NULL) {
            *capacity = 10;
            int *new_arr = (int*)realloc(*preOrderArray, (*capacity) * sizeof(int));
            *preOrderArray = new_arr;
            (*preOrderArray)[*current_size] = root->val;
            (*current_size)++;
        } else {
            return; //vetor vazio
        }
    }

    if(root->left != NULL) {
        if (*current_size == *capacity) {
            *capacity *= 2; //dobra o tamanho
            int *new_arr = (int*)realloc(*preOrderArray, (*capacity) * sizeof(int));
            *preOrderArray = new_arr;
        }

        (*preOrderArray)[*current_size] = root->left->val;
        (*current_size)++;
        fillArray(root->left, preOrderArray, capacity, current_size);
//quando ele volta pra cá com a chamada do 2 como raiz, ele não entra no outro if por que ele é um else if


    }
    
    if (root->right != NULL) {
        if (*current_size == *capacity) {
            *capacity *= 2; //dobra o tamanho
            int *new_arr = (int*)realloc(*preOrderArray, (*capacity) * sizeof(int));
            *preOrderArray = new_arr;
        }

        (*preOrderArray)[*current_size] = root->right->val;
        (*current_size)++;
        fillArray(root->right, preOrderArray, capacity, current_size);

    }
    
    if (root->left == NULL && root->right == NULL) {
        //faz um return com os valores pra caso isso aqui caia no caso de a root não ter nenhum filho
        return;
    }
    return;
}




/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    //The returnsize here contains the address of a variable. I'll fill it with the size I've found.
    int *preOrderArray = NULL;
    int capacity = 0;
    int current_size = 0;   

    fillArray(root, &preOrderArray, &capacity, &current_size);
    
    *returnSize = current_size;
    return preOrderArray;
}






// A simple utility function to create a new tree node.
// This is for building the test case tree in main.
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory for TreeNode");
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// A utility function to free the memory allocated for the tree.
// Good practice to prevent memory leaks in your local tests.
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// The main function to test your implementation.
// This will not be submitted to LeetCode.
int main() {
    // Construct a sample binary tree.
    // Example: [1, null, 2, 3]
    // The tree looks like this:
    //      1
    //       \
    //        2
    //       /
    //      3
    struct TreeNode* root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);

    // This is where your code will be called.
    int returnSize = 0;
    int* result = preorderTraversal(root, &returnSize);

    // Print the result to the console for verification.
    printf("Preorder Traversal: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Clean up allocated memory.
    free(result);
    freeTree(root);

    system("pause");
    return 0;
}