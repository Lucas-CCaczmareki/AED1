#include <stdio.h>
#include <stdlib.h>

/*
==================================
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
Ou seja, se n = 9 e tem 2 e 7 na posição 0 e 1 do vetor, o programa retorna 0 e 1 pois 2 + 7 = 9

A função recebe um array de números e o tamanho desse array
Recebe o target (resultado da soma) assumindo que só existe 1 e sempre é válido

O return size eu acho q é o array com as posições

A função retorna um ponteiro pro primeiro elemento do array
================================== */
int* twoSum(int* nums, int numsSize, int target, int* returnSize);

/*
==================================
Main
Calls the function
================================== */
int main( void ) {
    int nums[] = {3, 3}; 
    int result[2];
    int* returnSize;
    int numSize = 2;
    int target = 6;

    system("cls");

    returnSize = twoSum(nums, numSize, target, result);
    printf( "[%d, %d]", returnSize[0], returnSize[1] );
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i, j;
    //sei lá por que mas o site queria muito essa declaração assim
    *returnSize = 2; 
    int* indices = (int *)malloc(*returnSize * sizeof(int));

    for( i = 0; i < numsSize; i++) {
        //Aqui o j = i + 1 serve para evitar comparação entre o mesmo número, tipo nums[1] + nums[1]
        for( j = i + 1; j < numsSize; j++ ) {
            if( ( nums[i] + nums[j] ) == target ) {
                indices[0] = i;
                indices[1] = j;
                return indices;
            } 
        }
    }
    return NULL;
}