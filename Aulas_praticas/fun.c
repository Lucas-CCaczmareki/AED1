#include <stdio.h>
#include <stdlib.h>

int fun(int n){
    int count = 0, i, j;
    for (i = n; i > 0; i /= 2)
        for (j = 0; j < i; j++)
            count += 1;
            printf("%d\n", count);
    return count;
}

int main () {
    fun(10);
}

