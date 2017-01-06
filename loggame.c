#include "loggame.h"
#include "menu.h"
#include "tempo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define TYPES_SIZE 5

const char logFileName[] = "logGame.txt";
const char * nameOfTypeOfGameModes[] = {"VERY_EASY", "EASY", "NORMAL", "HARD", "VERY_HARD"};

void logGame() {
    FILE * logFile = NULL;

    if (!logFileExists()) {
        fprintf(stdout, "\n Nao ha records para serem exibidos!\n\n");
        return;
    }

    logFile = fopen(logFileName, "r+");

    int c;
    while((c = getc(logFile)) != EOF) {
        putchar(c);
    }
    fclose(logFile);
}

int logFileExists() {
    FILE * logFile = fopen(logFileName, "r");

    if(!logFile) {
        return FALSE;
    }

    fclose(logFile);
    return TRUE;
}

GAME_MODE getMode(int * size, int * mines) {

    if (*size == GRANDE && *mines == POUCAS) {
        return VERY_EASY;
    } else if ((*size == GRANDE && *mines == MEDIA) || (*size == MEDIANO && *mines == POUCAS)) {
        return EASY;
    } else if (*size == MEDIANO && *mines == MEDIA) {
        return NORMAL;
    } else if ((*size == MEDIANO && *mines == MUITAS) || (*size == PEQUENO && *mines == MEDIA)) {
        return HARD;
    } else if (*size == PEQUENO && *mines == MUITAS) {
        return VERY_HARD;
    }
    return EASY;
}

void writeInLog(TEMPO * gameTime, char nome[], int *size, int *mines) {

    GAME_MODE gameMode = getMode(size, mines);

    FILE * logFile;

    if (!logFileExists()) {
        logFile = fopen(logFileName, "w");;
    } else {
        logFile = fopen(logFileName, "r+");
    }

    fseek(logFile, 0, SEEK_END);

    fprintf(logFile, "NOME: %sMODO: %s\nTEMPO:", nome, nameOfTypeOfGameModes[gameMode]);
    printTimeInFile(logFile, gameTime);
    fclose(logFile);
}


