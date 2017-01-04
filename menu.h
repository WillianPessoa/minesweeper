#ifndef MENU_H
#define MENU_H

typedef struct _GRID GRID; // Forward declaration

typedef enum _OPTIONS {
    EXIT,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH,
    NULL_OPTION
}OPTIONS;

typedef enum _SIZE {
    PEQUENO = 5,
    MEDIANO = 10,
    GRANDE = 15
}SIZE;

typedef enum _MINES {
    POUCAS = 5,
    MEDIA = 10,
    MUITAS = 15
}MINES;

void launchMenu(GRID *grid);

void preGame(int * size, int * mines);

void mainMenu(int * mainOp);

void setupMenu(int * size, int * mines);

void defSizeMenu(int * size);

void defMinesMenu(int * mines, int * size);

#endif // MENU_H
