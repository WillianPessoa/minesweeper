#ifndef MINESWEEPER_H
#define MINESWEEPER_H

//EXEMPLO: Função declarada neste arquivo. Veja "minesweeper.c".
void testFunction();

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
    FIELD ** fields;  // Matriz de estruturas do tipo FIELD;
    int size;       // Tamanho do grid. Contém o tamanho de FIELDs por em cada linha e linhas de mesmo tamanho.
    int mines;      // Quantidade de minas no grid;
}GRID;

/** "CONSTRUTOR" DO GRID
 *  Uma função que cria um GRID com um determinado tamanho e número de minas
 *  Esse é um modelo inicial. Podemos definir macros em relação ao tamanho do grid
 *  e dificuldade e, assim, não não precisaremos passar muitos argumentos para as funções.
 */
GRID * makeAGrid(int size, int mines);

/** EXIBIR GRID NA TELA DO CONSOLE
 *  Exibira somente o grid. Outras coisas relacionadas ao console, irão ser manipuladas
 *  pelas funções responsáveis por isso. O objetivo é criar uma ortoganalidade do código
 */
void showGrid(GRID * grid);

/** EXIBIR GRID REVELADO */
void showGridRevelead(GRID * grid);

/** FUNÇÃO CLICADORA DE CAMPO
 *  O usuário irá "clicar" no campo declarando a posição x e y no grid.
 *  Uma outra em coisa em pauta é o tipo do Click. Ele pode ser um click para abrir o campo
 *  ou um click para marcar o campo. Podemos definir isso com um "enum" ou criar outra função
 *  para marcar.
 *
 *  A função ficaria com a forma:
 *
 * typedef enum _TypeOfClick {
 *  OPEN,
 *  MARK,
 *  }TypeOfClick;
 *
 * void clickIn(int pos_x, int pos_y, GRID * grid, typeOfClick type);
 */
void clickIn(int pos_x, int pos_y, GRID * grid,char typeOfClick);

/** FUNÇÃO PLANTADORA DE MINAS */
void plantMinesIn(GRID *grid, int minesToPlant);

/** FUNÇÃO PARA CALCULAR MINAS PRÓXIMAS
 *  Chamada dentro da função solver
 *  Essa função irá verificar quantas minas existem em volta do campo
 *  e alterará o membro "nearBombs"
 */
void checkNearMines(FIELD * field, GRID *grid);

/** FUNÇÃO INCREMENTAR O ATRIBUTO "MINAS PRÓXIMAS" EM TORNO DE UMA BOMBA SETADA
 *  Abordagem diferente da função de cima. Pode ser chamada sempre que uma bomba for posta
 *  em um determinado campo. Creio que essa função temuma abordagem mais otimizada.
 *  Não apagarei a CheckNearBombs por enquanto.
 */
void setNearMinesAround(FIELD * field, GRID *grid);

/** FUNÇÃO "SOLUCIONADORA" (FALTOU CRIATIVIDADE AQUI)
 *  Percorrerá o grid a partir do campo clicado em busca de um campo(na verdade vários)
 *  com minas próximas.
 */
void solver(FIELD * field, GRID * grid);


#endif // MINESWEEPER_H
