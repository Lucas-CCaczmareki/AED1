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

int* fillArray(struct TreeNode* root, int* preOrderArray, int i) {
    if(i == 0) {
        if(root != NULL) {
            preOrderArray[i] = root->val;
            i++;
        } else {
            return NULL; //vetor vazio
        }
    }

    if(root->left != NULL) {
        preOrderArray[i] = root->left->val;
        i++;
        fillArray(root->left, preOrderArray, i);
    } else if (root->right != NULL) {
        preOrderArray[i] = root->right->val;
        i++;
        fillArray(root->right, preOrderArray, i);
    } else {
        //faz um return com nada por que tamo só preenchendo
        return preOrderArray;
    }
}




/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    //The returnsize here contains the address of a variable. I'll fill it with the size I've found.
    int *preOrderArray = malloc(returnSize);
    preOrderArray = fillArray(root, preOrderArray, 0);

    
    
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

    return 0;
}