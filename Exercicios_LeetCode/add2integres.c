#include <stdio.h>

/*
============================
Sum
returns the sum of 2 numbers
============================
*/

int Sum( int num1, int num2 ) {
    return num1 + num2;
}

/*
============================
Main
Calls the function
============================
*/

int main( void ) {
    int num1 = 5, 
        num2 = 7,
        sum = Sum(num1, num2);

    printf("The sum of %d + %d is %d", num1, num2, sum);
}

