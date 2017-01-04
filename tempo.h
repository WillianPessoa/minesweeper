#ifndef TIME_H
#define TIME_H

#include <time.h>

typedef struct _TEMPO{
    int segundos;
    int minutos;
    int horas;
}TEMPO;

TEMPO * calcGameTimer(time_t *gameTimer);

void startGameTimer(time_t * gameTimer);

#endif
