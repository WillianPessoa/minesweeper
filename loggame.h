#ifndef RECORDS_H
#define RECORDS_H

/** Forward Declarations */
typedef enum _SIZE SIZE;
typedef enum _MINES MINES;
typedef struct _TEMPO TEMPO;

typedef enum _GAME_MODE{
    VERY_EASY,  // TAM: GRANDE / MINAS: POUCAS
    EASY,       // TAM: GRANDE / MINAS: MEDIA || TAM: MEDIANO / MINAS: POUCAS
    NORMAL,     // TAM: MEDIANO / MINAS: MEDIA
    HARD,       // TAM: MEDIA / MINAS: MUITAS || TAM: PEQUENO / MINAS: MEDIA
    VERY_HARD   // TAM: PEQUENO / MINAS: MUITAS
}GAME_MODE;

/** EXIBE O LOG/RECORDS DO JOGO */
void records();

/** VERIFICA SE O ARQUIVO DE LOG EXISTE */
int logFileExists();

/** RETORNA O MODO DE JOGO BASEADO NA QUANTIDADE DE MINAS E TAMANHO DO GRID */
GAME_MODE getMode(int *size, int *mines);

/** ESCREVE O RECORD NO GRID */
void writeRecord(TEMPO *gameTime, char nome[], int * size, int * mines);

#endif // RECORDS_H
