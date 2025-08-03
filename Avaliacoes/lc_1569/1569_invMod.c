//Essa aqui eu não entendi direito

#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX 1001  // máximo tamanho de input do problema

long long fact[MAX], invFact[MAX];

// Exponenciação modular: (base^exp) % MOD
long long modPow(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

// Pré-cálculo de fatoriais e inversos modulares
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    // Inverso de fact[MAX - 1] usando Fermat (MOD é primo)
    invFact[MAX - 1] = modPow(fact[MAX - 1], MOD - 2);
    for (int i = MAX - 2; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// Calcula combinações (n C k) % MOD
long long combinations(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (((fact[n] * invFact[k]) % MOD) * invFact[n - k]) % MOD;
}

// Função recursiva principal
long long dfs(int* nums, int numsSize) {
    if (numsSize < 3)
        return 1;

    int root = nums[0];
    int* left = (int*)malloc(sizeof(int) * numsSize);
    int* right = (int*)malloc(sizeof(int) * numsSize);
    int l = 0, r = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < root)
            left[l++] = nums[i];
        else
            right[r++] = nums[i];
    }

    long long waysLeft = dfs(left, l) % MOD;
    long long waysRight = dfs(right, r) % MOD;
    long long totalWays = combinations(l + r, l);  // formas de distribuir

    long long result = (((totalWays * waysLeft) % MOD) * waysRight) % MOD;

    free(left);
    free(right);
    return result;
}

// Função principal
int numOfWays(int* nums, int numsSize) {
    precompute();  // prepara fatoriais antes de tudo
    return (dfs(nums, numsSize) - 1 + MOD) % MOD;  // -1 pois não conta a ordem original
}