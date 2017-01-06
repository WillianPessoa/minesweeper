#include "tempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startGameTimer(time_t * gameTimer)
{
    *gameTimer = time(NULL); //alimenta a variavel tempo_i com Null para poder a contar;
}

void printTime(TEMPO * tempo_total)
{
    FILE * file = stdout;

    fprintf(file, "O tempo de duracao total foi de ");

    printTimeInFile(file, tempo_total);
}

void printTimeInFile(FILE * file, TEMPO * tempo_total)
{
    if (tempo_total->horas > 0) {
        fprintf(file, "%2d horas, ", tempo_total->horas);
    } else if (tempo_total->minutos >0) {
        fprintf(file, "%2d minutos e ", tempo_total->minutos);
    }

    fprintf(file, "%2d segundos.\n\n", tempo_total->segundos);
}

TEMPO * calcGameTimer(time_t *gameTimer) //como as funcoes de tempo vao estar seguidas, precisa-se guardar o tempo inicial e juntar com
{	//o tempo final, para poder pegar a diferenca. a funcao tempoFinal recebe uma variavel t1 do tipo time_t ;
    int segundos,aux1,aux2;
    TEMPO  * tempo_total = (TEMPO*) malloc(sizeof(TEMPO));
    time_t tempo_f;			//cria uma variavel tempo_f do tipo time_t;
    tempo_f = time(NULL);
    segundos = difftime(tempo_f, *gameTimer); //diferenca de tempo. Retorna um tempo em segundos do tipo int;
    if (segundos>60) //verifica se o jogo possui mais de um minuto de duracao;
    {
        aux1 = (int)segundos/60; //parte inteira da divisao de segundos por 60 (minutos);
        tempo_total->segundos = segundos%60; //resto da divisao de segundos por 60;
        tempo_total->minutos = aux1; //acrescenta 1 minuto;
        if (tempo_total->minutos > 60) //verifica se o jogo possui mais de uma hora de duracao;
        {
            aux2 = (int)tempo_total->minutos / 60; //parte inteira da divisao de minutos por 60 (horas);
            tempo_total->minutos %= 60; //resto da divisao por 60;
            tempo_total->horas = aux2;
        }
        else tempo_total->horas = 0; //caso a duracao nao tenha mais que 1 hora;

    }
    else //caso nao precise converter os segundos para minutos;
    {
        tempo_total->segundos = segundos;
        tempo_total->minutos = 0;
        tempo_total->horas = 0;
    }

    printTime(tempo_total);

    return tempo_total;
}
