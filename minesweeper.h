#ifndef MINESWEEPER_H
#define MINESWEEPER_H

typedef enum {
    LOSE,
    WIN,
    UNDEFINED
}GAME_RESULT;

typedef enum {
    GIVE_UP,
    REVEAL_CLICK,
    MARK_CLICK
}TYPE_OF_CLICK;

/** ESTRUTURA DA UNIDADE CAMPO */
typedef struct _FIELD {
    int pos_x;      // Posição no eixo x;
    int pos_y;      // Posição no eixo y;
    int mine;       // Indicador de bomba neste campo (true or false - definidas no .c);
    int revealed;   // Indicador de revelação do campo (true or false - definidas no .c);
    int marked;     // Indicador de marcação (true or false - definidas no .c);
    int nearMines;  // minas próximas;

}FIELD;

/** ESTRUTURA DO COLETIVO DE CAMPOS */
typedef struct _GRID {
    FIELD ** fields;// Matriz de estruturas do tipo FIELD;
    int size;       // Tamanho do grid. Contém o tamanho de FIELDs por em cada linha e linhas de mesmo tamanho.
    int mines;      // Quantidade de minas no grid;
    int toReveal;
}GRID;

/** "CONSTRUTOR" DO GRID */
void buildGridwith(GRID *grid, int size, int mines);

/** EXIBE O GRID NA TELA DO CONSOLE */
void showGrid(GRID * grid);

/** EXIBE GRID REVELADO */
void showGridRevelead(GRID * grid);

/** FUNÇÃO CLICADORA DE CAMPO */
int clickIn(GRID * grid, int pos_x, int pos_y, char typeOfClick);

/** FUNÇÃO QUE MARCA/DESMARCA UM CAMPO */
void markField(GRID * grid, int pos_x, int pos_y);

/** FUNÇÃO QUE REVELA O CAMPO E APLICA O SOLVER SE FOR VAZIO */
int revealField(GRID * grid, int pos_x, int pos_y);

/** FUNÇÃO PLANTADORA DE MINAS */
void plantMinesIn(GRID *grid, int minesToPlant, int except_pos_x, int except_pos_y);

/** FUNÇÃO PARA CALCULAR MINAS PRÓXIMAS */
void checkNearMines(FIELD * field, GRID *grid);

/** FUNÇÃO INCREMENTAR O ATRIBUTO "MINAS PRÓXIMAS" EM TORNO DE UMA BOMBA SETADA */
void setNearMinesAround(FIELD * field, GRID *grid);

/** FUNÇÃO QUE RECEBE COORDENADAS E TIPO DE CLICK VÁLIDOS */
void getValidsCommands(GRID * grid, int *pos_x, int *pos_y, char *typeOfClick);

/** FUNÇÃO "SOLUCIONADORA" (FALTOU CRIATIVIDADE AQUI) */
void solver(GRID * grid, int pos_x, int pos_y);
void revealNext(GRID * grid, int pos_x, int pos_y);

/** INICIA O JOGO */
int launchGame(GRID * grid, int size, int mines);

/** VAI QUE VAI */
void recursive_reveal(GRID * grid, int pos_x, int pos_y);

int rreveal(GRID * grid, int pos_x, int pos_y, int isRecursive);

#endif // MINESWEEPER_H
