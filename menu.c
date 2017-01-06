#include "menu.h"

#include "minesweeper.h"
#include "loggame.h"
#include "tempo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void launchMenu(GRID * grid) {

    int mainOp = NULL_OPTION;

    int size = MEDIANO;
    int mines = (size * size) * MEDIA / (double) 100;

    GAME_RESULT gameResult;

    time_t timer;
    TEMPO * gameTime;

    char name[SIZE_NAME];

    while (mainOp != EXIT) {

        fprintf(stdout, "\n**************MENU PRINCIPAL**************\n\n"
            "[1] Iniciar o jogo\n"
            "[2] Configuracoes\n"
            "[3] Ver records\n"
            "[4] Como jogar (regras)\n"
            "[0] Sair\n\n"
            "Opcao: ");

        while (fscanf(stdin, "%d", &mainOp) != EOF && (mainOp < EXIT || mainOp > FOURTH));

        switch (mainOp) {

        case FIRST:
            preGame( &size, &mines); // Pré-jogo -> exibe configurações de jogo atuais.
            startGameTimer( &timer); // Inicia o contador do tempo do jogo
            gameResult = launchGame(grid, size, mines); // Inicia o jogo e retorna o resultado.
            gameTime = calcGameTimer( &timer); // Encerra o contador do tempo do jogo;
            if (gameResult == WIN) {
                fprintf(stdout, "\nVoce ganhou! Digite seu nome para ser adicionado ao hall da fama: ");
                fgets(name, SIZE_NAME, stdin);
                writeInLog(gameTime, name, &size, &mines);
            }
            break;
        case SECOND:
            setupMenu( &size, &mines);
            break;
        case THIRD:
            fprintf(stdout, "\n\n*************** LOG GAME ***************\n\n");
            logGame();
            break;
        case FOURTH:
            showRules();
            break;
        }
    }

    fprintf(stdout, "\n********************AGRADECIMENTOS*******************\n\n");
    fprintf(stdout, "    Este jogo foi desenvolvido por Amanda Salles, \n  Aline Moura, Dennison Carvallo e Willian Pessoa.\n\n");
    fprintf(stdout, "           AGRADECEMOS POR TER JOGADO! S2\n\n");
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

    switch (decisionOp) {

    case SECOND:
        setupMenu(size, mines);
        preGame(size, mines);
        break;
    }
}

void showRules() {
    fprintf(stdout, "\n*************************************REGRAS*************************************\n\n"
        "   A area do jogo, variavel de acordo com o nivel de dificuldade selecionado \n"
        "(pequeno, mediano e grande) e a quantidade de minas selecionadas (10%%, 20%%\n"
        " ou 40%% do tamanho do grid.) consiste em uma grade de quadrados conhecidos\n "
        "como campos. Cada campo eh revelado quando clicado, e caso ele contenha\n"
        " uma mina, ela explode e o jogo acaba.\n\n"
        "   Neste jogo, o usuario selecionara o tipo de clique que ele deseja realizar\n"
        " e, em seguida, inserir as coordenadas do campo que ele deseja clicar. O click\n"
        " pode ser para revelar ou para marcar o campo. Um campo marcado tem a sinalizacao\n"
        " com um \"?\".\n\n"
        "   Ao final de cada jogo, eh exibido o tempo da partida e, se o jogador tiver vencido\n"
        " a partida, eh liberado a opcao de insercao de nome para ser registrado no logo do jogo.\n\n"
        "   A insercao consite do nome do jogador, o tempo de jogo e o modo (dificuldade) escolhida.\n"
        "A dificuldade eh estabelecida de acordo com os seguintes criterios.\n\n"
        "[*] MUITO FACIL -> Se o tamanho do grid for GRANDE e a quantidade de minas for de 10%%;\n\n"
        "[*] FACIL -> Se o tamanho do grid for GRANDE e a quantidade de minas for de 20%% ou\n"
        "             se a o tamanho do grid for MEDIANO e a quantidade de minas for de 10%%;\n\n"
        "[*] NORMAL -> Se o tamanho do grid for MEDIANO e a quantidade de minas for de 20%%;\n\n"
        "[*] DIFICIL -> Se o tamanho do grid for MEDIANO e a quantidade de minas for de 40%% OU\n"
        "              se o tamanho do grid for PEQUENO e a quantidade de minas for de 20%;\n\n"
        "[*] MUITO DIFICIL -> Se o tamanho do grid for PEQUENO e a quantidade de minas for de 40%%;\n\n");
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

        switch (setupOp) {

        case FIRST:
            defSizeMenu(size);
            defMinesMenu(mines, size);
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

    while ((fscanf(stdin, "%d", &sizeOp) != EOF) && (sizeOp < EXIT || sizeOp > THIRD));

    switch (sizeOp) {

    case FIRST:
        * size = PEQUENO;
        break;
    case SECOND:
        * size = MEDIANO;
        break;
    case THIRD:
        * size = GRANDE;
        break;
    }
}

void defMinesMenu(int * mines, int * size) {

    int minesOp = NULL_OPTION;

    fprintf(stdout, "\n**************DEF_MINES**************\n\n"
        "[1] Poucas (5%% do tamanho do grid)\n"
        "[2] Normal (10%% do tamanho do grid)\n"
        "[3] Muitas (15%% do tamanho do grid)\n\n"
        "[0] Voltar ");

    while ((fscanf(stdin, "%d", &minesOp) != EOF) && (minesOp < EXIT || minesOp > THIRD));

    switch (minesOp) {

    case FIRST:
        * mines = ((*size) * (*size)) * ((double) POUCAS / 100);
        break;
    case SECOND:
        * mines = ((*size) * (*size)) * ((double) MEDIA / 100);
        break;
    case THIRD:
        * mines = ((*size) * (*size)) * ((double) MUITAS / 100);
        break;
    }
}
