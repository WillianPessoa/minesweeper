#include "records.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define TYPES_SIZE 5

const char recordsFileName[] = "records.txt";
const int typesSize = 5;
const char * nameOfTypeOfRecords[] = {"VERY EASY", "EASY", "NORMAL", "HARD", "VERY HARD"};

typedef enum _TYPE_OF_RECORD{
    VERY_EASY,  // TAM: GRANDE / MINAS: MUITAS
    EASY,       // TAM: GRANDE / MINAS: MEDIA || TAM: MEDIANO / MINAS: POUCAS
    NORMAL,     // TAM: MEDIANO / MINAS: MEDIA
    HARD,       // TAM: MEDIA / MINAS: MUITAS || TAM: PEQUENO / MINAS: MEDIA
    VERY_HARD   // TAM: PEQUENO / MINAS: MUITAS
}TYPE_OF_RECORD;


void records() {
    if(!recordsFileExists()) {
        createRecordsFile();
    }

    FILE * recordsFile = fopen(recordsFileName, "r");
}

int recordsFileExists() {
    FILE * file = fopen(recordsFileName, "r");
    if(file) {
        fclose(file);
        return TRUE;
    }
    return FALSE;
}

void createRecordsFile() {
    FILE * recordsFile = fopen(recordsFileName, "w");
    int i;
    for (i = 0; i < typesSize; ++i) {
        fprintf(recordsFile, "#%s#\n", nameOfTypeOfRecords[i]);
    }
    fclose(recordsFile);
}
