#include <stdio.h>

/*
=========================================
Main
1. Escreva um trecho de codigo para fazer a criac¸ ´ ao dos novos tipos de dados conforme ˜
solicitado abaixo:
• Horario: composto de hora, minutos e segundos. ´
• Data: composto de dia, mes e ano. ˆ
• Compromisso: composto de uma data, horario e texto que descreve o compromisso.
=========================================
*/

struct horario {
    int hora;
    int min;
    int seg;
};

struct data {
    int dia;
    int mes;
    int ano;
};

struct compromisso {
    struct data data;
    struct horario horario;
    char text[1000];
};

int main( void ) {
    struct compromisso reuniao;

    reuniao.data.dia = 2;
    reuniao.data.mes = 5;
    reuniao.data.ano = 2025;

    reuniao.horario.hora = 18;

    printf ( "You have a meeting scheduled for: 0%d/0%d/%d at %d:00", reuniao.data.dia, reuniao.data.mes, reuniao.data.ano, reuniao.horario.hora);
}