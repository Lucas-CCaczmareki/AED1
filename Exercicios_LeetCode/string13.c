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
    strcpy(s, "XLIV"); //create the string with the roman numbers

    n = romanToInt(s);
    printf( "%d", n );
}

int romanToInt(char* romanN) {
    //char romanN[100];
    char *specialCase[6] = {"IV", "IX", "XL", "XC", "CD", "CM"};
    int i = 0, j = 0;
    int total = 0;
    bool f_specialCase = false;

    //strcpy(romanN, "XLIV");

    while( romanN[i] != '\0' ) {
        //isso aqui vai dar problemas com os IX e IV da vida.
        //então eu só entro nesse switch se não houver IX e IV da vida e faço um caso especial caso tenha.
        for( j = 0; j < 6; j++ ) {
            if( strstr(romanN, specialCase[j]) != NULL ) { //isso significa que encontrou
                f_specialCase = true;
            }
        }

        if (f_specialCase) { //se for true
            //vou precisar comparar 2 a 2, e ver se é uma ocorrência especial
            switch (romanN[i]) {
            case 'I':
                if( romanN[i+1] == 'V' ) {
                    total += 4;
                    i++;
                } else if( romanN[i+1] == 'X' ) {
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
                if( romanN[i+1] == 'L' ) {
                    total += 40;
                    i++;
                } else if( romanN[i+1] == 'C' ) {
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
                if( romanN[i+1] == 'L' ) {
                    total += 400;
                    i++;
                } else if( romanN[i+1] == 'C' ) {
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
        } else {
            switch (romanN[i]) {
            case 'I':
                total += 1;
                break;
            
            case 'V':
                total += 5;
                break;

            case 'X':
                total += 10;
                break;
            
            case 'L':
                total += 50;
                break;

            case 'C':
                total += 100;
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
        }
        i++;
    }
    return total;
}