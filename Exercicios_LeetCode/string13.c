#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
============================================
romanToInt
Receives a string with roman number
and convert roman to integer.
============================================
*/
int romanToInt(char* s);

/*
============================================
Main
Calls the romanToInt function
============================================
*/
int main ( void ) {
    char s[100];
    int n;
    strcpy(s, "MCMXCIV"); //create the string with the roman numbers

    n = romanToInt(s);
    printf( "%d", n );
}

int romanToInt(char* s) {
    int i = 0;
    int total = 0;

    //Loopa até o final da string
    while( s[i] != '\0' ) {
        switch (s[i]) { //faz a soma com base no primeiro e no segundo caractere, considerando casos especiais
        case 'I':
            if( s[i+1] == 'V' ) {
                total += 4;
                i++;
            } else if( s[i+1] == 'X' ) {
                total += 9;
                i++;
            } else {
                total += 1;
            }
            break;
        
        case 'V':
            total += 5;
            break;

        case 'X':
            if( s[i+1] == 'L' ) {
                total += 40;
                i++;
            } else if( s[i+1] == 'C' ) {
                total += 90;
                i++;
            } else {
                total += 10;
            }
            break;
        
        case 'L':
            total += 50;
            break;

        case 'C':
            if( s[i+1] == 'D' ) {
                total += 400;
                i++;
            } else if( s[i+1] == 'M' ) {
                total += 900;
                i++;
            } else {
                total += 100;
            }
            break;

        case 'D':
            total += 500;
            break;

        case 'M':
            total += 1000;
            break;
        
        default:
            break;
        }
        i++;
    }
    return total;
}