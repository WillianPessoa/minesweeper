#include "menu.h"

#include "minesweeper.h"
#include "records.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    PEQUENO = 15,
    MEDIO = 30,
    GRANDE = 60
}MINES;

typedef enum _QMINES {
    POUCAS = 15,
    NORMAL = 30,
    MUITAS = 60
}QMINES;

void launchMenu(GRID * grid) {

    int mainOp = NULL_OPTION;

    int size = MEDIO;
    int mines = size * (NORMAL/100);

    while (mainOp != EXIT) {

        fprintf(stdout, "\n**************MENU PRINCIPAL**************\n\n"
                        "[1] Iniciar o jogo\n"
                        "[2] Configuracoes\n"
                        "[3] Ver records\n"
                        "[0] Sair\n\n"
                        "Opcao: ");

        while (fscanf(stdin, "%d", &mainOp) != EOF && (mainOp < EXIT || mainOp > THIRD));

        switch(mainOp) {

        case FIRST:
            //INIT GAME
            break;
        case SECOND:
            setupMenu(&size, &mines);
            break;
        case THIRD:
            records();
            break;
        }
    }
}

void setupMenu(int * size, int * mines) {
    int setupOp = NULL_OPTION;

    while (setupOp != EXIT) {

        fprintf(stdout, "\n**************SETUP**************\n\n"
                        "[1] Definir tamanho do grid\n"
                        "[2] Definir quantidade de minas\n"
                        "[0] Voltar\n\n"
                        "Opcao: ");

        while (fscanf(stdin, "%d", &setupOp) != EOF && (setupOp < EXIT || setupOp > SECOND));

        switch(setupOp) {

        case FIRST:
            defSizeMenu(size);
            setupOp = NULL_OPTION;
            break;
        case SECOND:
            defMinesMenu(mines, size);
            setupOp = NULL_OPTION;
            break;
        }
    }
}

void defSizeMenu(int * size) {

    int sizeOp = NULL_OPTION;

    fprintf(stdout, "\n**************DEF_SIZE**************\n\n"
                    "[1] Pequeno\n"
                    "[2] Medio\n"
                    "[3] Grande\n\n"
                    "[0] Voltar ");

    while (fscanf(stdin, "%d", &sizeOp) != EOF && (sizeOp < EXIT || sizeOp > THIRD));

    switch(sizeOp) {

    case FIRST:
        *size = PEQUENO;
        break;
    case SECOND:
        *size = MEDIO;
        break;
    case THIRD:
        *size = GRANDE;
        break;
    }
}

void defMinesMenu(int * mines, int *size) {

    int minesOp = NULL_OPTION;

    fprintf(stdout, "\n**************DEF_MINES**************\n\n"
                    "[1] Poucas (10%% do tamanho do grid)\n"
                    "[2] Normal (30%% do tamanho do grid\n"
                    "[3] Muitas (60%% do tamanho do grid\n\n"
                    "[0] Voltar ");

    while (fscanf(stdin, "%d", &minesOp) != EOF && (minesOp < EXIT || minesOp > THIRD))

    switch(minesOp) {

    case FIRST:
        *mines = *size * (POUCAS/100);
        break;
    case SECOND:
        *mines = *size * (NORMAL/100);
        break;
    case THIRD:
        *mines = *size * (MUITAS/100);
        break;
    }
}
