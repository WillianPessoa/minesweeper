#ifndef MENU_H
#define MENU_H

#define SIZE_NAME 40

typedef struct _GRID GRID; // Forward declaration

typedef enum _OPTIONS {
    EXIT,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    NULL_OPTION
}OPTIONS;

typedef enum _SIZE {
    PEQUENO = 5,
    MEDIANO = 10,
    GRANDE = 15
}SIZE;

typedef enum _MINES {
    POUCAS = 15,
    MEDIA = 30,
    MUITAS = 60
}MINES;

/** INICIA O MENU */
void launchMenu(GRID * grid);

/** MENU PRÉ-JOGO, EXIBE COMO O JOGO ESTÁ CONFIGURADO
 *  É chamada recursivamente sempre que o jogador decidir alterar as configurações de jogo */
void preGame(int * size, int * mines);

/** Exibe as regras do jogo */
void showRules();

/** MENU PRINCIPAL */
void mainMenu(int * mainOp);

/** MENU DE CONFIGURAÇÃO */
void setupMenu(int * size, int * mines);

/** MENU PARA DEFINIR O TAMANHO */
void defSizeMenu(int * size);

/** MENU PARA DEFINIR A QUANTIDADE DE MINAS */
void defMinesMenu(int * mines, int * size);

#endif // MENU_H
