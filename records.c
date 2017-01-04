#include "records.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define TYPES_SIZE 5

const char recordsFileName[] = "logGame.txt";
const char * nameOfTypeOfRecords[] = {"VERY_EASY", "EASY", "NORMAL", "HARD", "VERY_HARD"};

void records() {
    FILE * logFile = NULL;

    if (!logFileExists()) {
        logFile = fopen(recordsFileName, "w");;
    } else {
        logFile = fopen(recordsFileName, "r+");
    }

}

int logFileExists() {
    FILE * logFile = fopen(recordsFileName, "r");

    if(!logFile) {
        return FALSE;
    }

    fclose(logFile);
    return TRUE;
}


