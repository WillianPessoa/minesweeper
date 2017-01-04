#include "menu.h"

#include "minesweeper.h"
#include "records.h"
#include "tempo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void launchMenu(GRID * grid) {

    int mainOp = NULL_OPTION;

    int size = MEDIANO;
    int mines = (size*size) * MEDIA/100;

    GAME_RESULT gameResult;

    time_t timer;
    TEMPO * gameTime;

    while (mainOp != EXIT) {

        fprintf(stdout, "\n**************MENU PRINCIPAL**************\n\n"
                        "[1] Iniciar o jogo\n"
                        "[2] Configuracoes\n"
                        "[3] Ver records\n"
                        "[0] Sair\n\n"
                        "Opcao: ");

        while (fscanf(stdin, "%d", &mainOp) != EOF && (mainOp < EXIT || mainOp > THIRD));

        switch (mainOp) {

        case FIRST:
            preGame(&size, &mines);     // Pré-jogo -> exibe configurações de jogo atuais.
            startGameTimer(&timer); // Inicia o contador do tempo do jogo
            gameResult = launchGame(grid, size, mines); // Inicia o jogo e retorna o resultado.
            gameTime = calcGameTimer(&timer);   // Encerra o contador do tempo do jogo;
            if (gameResult == WIN) {

            }


            break;
        case SECOND:
            setupMenu(&size, &mines);
            break;
        case THIRD:
            //records();
            break;
        }
    }
}

void preGame(int * size, int * mines) {

    int decisionOp = NULL_OPTION;

    fprintf(stdout, "\n*********INICIANDO JOGO*********\n\n"
                    "O jogo foi esta definido para iniciar com tamanho %d\n"
                    " e quantidade de minas igual a %d\n\n"
                    "[1] Iniciar o jogo\n"
                    "[2] Ir no menu de configuracao\n\n"
                    "Opcao: ", *size, *mines);

    while (fscanf(stdin, "%d", &decisionOp) != EOF && (decisionOp < FIRST || decisionOp > SECOND));

    switch(decisionOp) {

    case SECOND:
        setupMenu(size, mines);
        break;
    }

    fprintf(stdout, "\n\nINICIALIZANDO O JOGO...\n");

    unsigned int i;
    for(i = 0; i < 599999999; ++i) {}
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
                    "[1] Pequeno (5x5)\n"
                    "[2] Medio (10x10)\n"
                    "[3] Grande (15x15)\n\n"
                    "[0] Voltar ");

    while (fscanf(stdin, "%d", &sizeOp) != EOF && (sizeOp < EXIT || sizeOp > THIRD));

    switch(sizeOp) {

    case FIRST:
        *size = PEQUENO;
        break;
    case SECOND:
        *size = MEDIANO;
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
                    "[2] Normal (30%% do tamanho do grid)\n"
                    "[3] Muitas (60%% do tamanho do grid)\n\n"
                    "[0] Voltar ");

    while (fscanf(stdin, "%d", &minesOp) != EOF && (minesOp < EXIT || minesOp > THIRD))

    switch(minesOp) {

    case FIRST:
        *mines = ((*size)*(*size)) * (POUCAS/100);
        break;
    case SECOND:
        *mines = ((*size)*(*size)) * (MEDIA/100);
        break;
    case THIRD:
        *mines = ((*size)*(*size)) * (MUITAS/100);
        break;
    }
}
