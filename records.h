#ifndef RECORDS_H
#define RECORDS_H

/** Forward Declarations */
typedef enum _SIZE SIZE;
typedef enum _MINES MINES;

typedef enum _TYPE_OF_RECORD{
    VERY_EASY,  // TAM: GRANDE / MINAS: MUITAS
    EASY,       // TAM: GRANDE / MINAS: MEDIA || TAM: MEDIANO / MINAS: POUCAS
    NORMAL,     // TAM: MEDIANO / MINAS: MEDIA
    HARD,       // TAM: MEDIA / MINAS: MUITAS || TAM: PEQUENO / MINAS: MEDIA
    VERY_HARD   // TAM: PEQUENO / MINAS: MUITAS
}TYPE_OF_RECORD;

void records();

int logFileExists();


#endif // RECORDS_H
