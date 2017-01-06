#ifndef TIME_H
#define TIME_H

#include <time.h>
#include <stdio.h>

typedef struct _TEMPO{
    int segundos;
    int minutos;
    int horas;
}TEMPO;

/** CALCULA O TEMPO DE JOGO E O IMPRIME NA TELA */
TEMPO * calcGameTimer(time_t *gameTimer);

/** INICIA A VARIÁVEL COM O TEMPO ATUAL DA MÁQUINA */
void startGameTimer(time_t * gameTimer);

/** IMPRIME O TEMPO DE JOGO NA TELA */
void printTime(TEMPO * tempo_total);

/** IMPRIME O TEMPO DE JOGO NUM ARQUIVO */
void printTimeInFile(FILE * file, TEMPO * tempo_total);

#endif
