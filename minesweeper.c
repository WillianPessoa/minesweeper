#include "minesweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define INVALID_COORD -1

#define GRID_MAX_SIZE 30

const char flag = '?';
const char notClicked = '*';
const char mined = 'M';

//Fun??o que remove o "\n" chato.
void clear_newlines(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Retorna um grid constru?do com o tamanho m?ximo
GRID * buildGrid(int size, int mines) {
    GRID * grid = malloc(sizeof(grid));

    // Atribui ao Grid o tamanho e a quantidade de bombas que este deve conter;
    grid->size = size;
    grid->mines = mines;
    grid->toReveal = size - mines;

    // Constr?i o grid;
    grid->fields = malloc(size * sizeof(FIELD * ));

    int i, j;
    for (i = 0; i < size; ++i) {
        grid-> fields[i] = malloc(size * sizeof(FIELD));

        // Atribui os valores padr?es para cada campo;
        for (j = 0; j < size; ++j) {
            grid->fields[i][j].pos_x = i;
            grid->fields[i][j].pos_y = j;
            grid->fields[i][j].mine = FALSE;
            grid->fields[i][j].marked = FALSE;
            grid->fields[i][j].revealed = FALSE;
            grid->fields[i][j].nearMines = 0;
        }
    }
    return grid;
}

// Exibe o grid de acordo com o estado de cada campo.
void showGrid(GRID * grid) {
    int i, j;

    fprintf(stdout, "\n***************** GRID *****************\n\n");

    for (i = 0; i < grid->size; ++i) {

        if (i == 0) {
            int k;
            fprintf(stdout, "  ");

            for (k = 0; k < grid->size; ++k) {
                fprintf(stdout, " %d", k);
                if (k < 10) {
                    fprintf(stdout, " ");
                }
            }
            fprintf(stdout, "\n");
        }

        fprintf(stdout, "%d", i);

        if (i < 10) {
            fprintf(stdout, " ");
        }

        for (j = 0; j < grid->size; ++j) {

            // Se o campo estiver marcado, exibe a sinaliza??oo de marca??o;
            if (grid->fields[i][j].marked) {
                fprintf(stdout, "[%c]", flag);
            }

            // Se o campo j? foi revelado...;
            else if (grid->fields[i][j].revealed) {

                //... e se o campo possuir bombas pr?ximas, exibe a quantidade;
                if (grid->fields[i][j].nearMines != 0) {
                    fprintf(stdout, "[%d]", grid->fields[i][j].nearMines);
                }
                //... e se n?o possuir bombas próximas, exibe a sinaliza??o de um campo vazio;
                else {
                    fprintf(stdout, "[ ]");
                }
            }

            //Se n?oo tiver sido clicado, exibe a sinalização de não clicado.
            else {
                fprintf(stdout, "[%c]", notClicked);
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void showGridRevelead(GRID * grid) {
    int i, j;

    fprintf(stdout, "\n***************** GRID *****************\n\n");

    for (i = 0; i < grid->size; ++i) {

        if (i == 0) {
            int k;
            fprintf(stdout, "  ");

            for (k = 0; k < grid->size; ++k) {
                fprintf(stdout, " %d", k);
                if (k < 10) {
                    fprintf(stdout, " ");
                }
            }
            fprintf(stdout, "\n");
        }

        fprintf(stdout, "%d", i);

        if (i < 10) {
            fprintf(stdout, " ");
        }

        for (j = 0; j < grid->size; ++j) {

            if (grid->fields[i][j].mine == TRUE) {
                fprintf(stdout, "[%c]", mined);
            } else if (grid->fields[i][j].nearMines != 0) {
                fprintf(stdout, "[%d]", grid->fields[i][j].nearMines);
            } else {
                fprintf(stdout, "[ ]");
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

// Planta a quantidade de minas no grid aleatoriamente.
void plantMinesIn(GRID * grid, int minesToPlant, int except_pos_x, int except_pos_y) {
    srand(time(NULL));

    int size = grid->size;

    int pos_x;
    int pos_y;

    int minesPlanted;

    for (minesPlanted = 0; minesPlanted < minesToPlant; ++minesPlanted) {
        pos_x = rand() % size;
        pos_y = rand() % size;

        if (pos_x == except_pos_x && pos_y == except_pos_y) {
            --minesPlanted;
            continue;
        }

        if (grid->fields[pos_x][pos_y].mine == FALSE) {
            grid->fields[pos_x][pos_y].mine = TRUE;
            setNearMinesAround(&grid->fields[pos_x][pos_y], grid);
        } else {
            --minesPlanted;
            continue;
        }
    }
    grid->mines = minesPlanted;

}

// Percorre o entorno de um campo, verifica quantas bombas existem em volta e incrementa
// o atributo "nearBombs" de acordo
void checkNearMines(FIELD * field, GRID * grid) {
    int i, j;

    // Reseta o membro "nearBombs"
    field->nearMines = 0;

    //Definindo minimos e máximos
    int min_x = field->pos_x == 0 ? field->pos_x : field->pos_x - 1;
    int max_x = field->pos_x == grid->size - 1 ? field->pos_x : field->pos_x + 1;

    int min_y = field->pos_y == 0 ? field->pos_y : field->pos_y - 1;
    int max_y = field->pos_y == grid->size - 1 ? field->pos_y : field->pos_y + 1;

    // Percorre o entorno...
    for (i = min_x; i <= max_x; ++i) {
        for (j = min_y; j <= max_y; ++j) {
            if (i == field->pos_x && j == field->pos_y) {
                continue;
            }
            // ... e incrementa para cada bomba achada.
            if (grid->fields[i][j].mine) {
                ++field->nearMines;
            }
        }
    }
}

// Percorre o entorno de um campo que possui uma bomba, e incrementa o "nearBombs"
// de cada campo adjacente.
void setNearMinesAround(FIELD * field, GRID * grid) {
    int i, j;

    //Definindo minimos e maximos
    int min_x = field->pos_x == 0 ? field->pos_x : field->pos_x - 1;
    int max_x = field->pos_x == grid->size - 1 ? field->pos_x : field->pos_x + 1;

    int min_y = field->pos_y == 0 ? field->pos_y : field->pos_y - 1;
    int max_y = field->pos_y == grid->size-1 ? field->pos_y : field->pos_y + 1;

    //Percorre o entorno de acordo com os minimos e maximos encontrados.
    for (i = min_x; i <= max_x; ++i) {
        for (j = min_y; j <= max_y; ++j) {
            if (i == field->pos_x && j == field->pos_y) {
                continue;
            }
            // e incrementa o "nearBombs" de cada um.
            ++grid->fields[i][j].nearMines;
        }
    }
}

int clickIn(GRID * grid, int pos_x, int pos_y, char typeOfClick) {

    static int clickCount = 0;

    if (clickCount == 0) {
        plantMinesIn(grid, grid->mines, pos_x, pos_y);
    }
    ++clickCount;

    switch (typeOfClick) {

    case 'r':
        return rreveal(grid, pos_x, pos_y, FALSE);
        break;

    case 'm':
        markField(grid, pos_x, pos_y);
        break;

    case 'o':
        return LOSE;
        break;

    default:
        fprintf(stdout, "\n Comando %c eh invalido!\n\n", typeOfClick);
        break;
    }

    return UNDEFINED;
}

void markField(GRID * grid, int pos_x, int pos_y) {

    if (grid->fields[pos_x][pos_y].revealed == FALSE) {

        if (grid->fields[pos_x][pos_y].marked == FALSE) {
            grid->fields[pos_x][pos_y].marked = TRUE;
        } else {
            grid->fields[pos_x][pos_y].marked = FALSE;
        }
    }
}

void getValidsCommands(GRID * grid, int * pos_x, int * pos_y, char * typeOfClick) {

    TYPE_OF_CLICK click;

    fprintf(stdout, "Que tipo de Click?\n"
        "[1] Revelar\n"
        "[2] Marcar\n"
        "[0] Desistir\n\n"
        "Click: ");

    while (fscanf(stdin, "%u", & click) != EOF && (click < GIVE_UP || click > MARK_CLICK));
    clear_newlines();

    switch (click) {

    case GIVE_UP:
        * typeOfClick = 'o'; // Desiste.
        return;
    case REVEAL_CLICK:
        * typeOfClick = 'r'; // revela
        break;
    case MARK_CLICK:
        * typeOfClick = 'm'; // Marca
        break;
    }

    fprintf(stdout, "\nInsira as coordenadas do click: \n");

    fprintf(stdout, "Cord. X: ");
    while (fscanf(stdin, "%d", pos_x) != EOF && ( *pos_x < 0 || *pos_x > grid->size - 1));
    clear_newlines();

    fprintf(stdout, "Cord. Y: ");
    while (fscanf(stdin, "%d", pos_y) != EOF && ( *pos_y < 0 || *pos_y > grid->size - 1));
    clear_newlines();
}

int launchGame(GRID * grid, int size, int mines) {

    //Constroi o grid
    grid = buildGrid(size, mines);

    //Variavel que armazenara o resultado o jogo
    GAME_RESULT gameResult = UNDEFINED;

    //Inicializando as variaveis das coordenadas com valores invalidos.
    int pos_x = INVALID_COORD;
    int pos_y = INVALID_COORD;
    char typeOfClick = '0';

    //Enquanto o jogo nao tiver um resultado definido...
    while (gameResult == UNDEFINED) {

        showGrid(grid); // ...exibe o grid,...

        getValidsCommands(grid, &pos_x, &pos_y, &typeOfClick); // ... recebe os comandos validos (coordenadas e tipo do click)...

        if (typeOfClick == 'o') {
            gameResult = LOSE;
            break;
        }

        gameResult = clickIn(grid, pos_x, pos_y, typeOfClick); // ... e realiza o click no grid aplicando o solver, se necessario.

        if (grid->toReveal == 0) {
            gameResult = WIN;
        }
    }

    showGridRevelead(grid);

    switch (gameResult) {

    case WIN:
        fprintf(stdout, "\nVOCE GANHOU!\n");
        break;
    case LOSE:
        fprintf(stdout, "\nVOCE PERDEU!\n");
        break;
    }

    return gameResult;
}

int rreveal(GRID * grid, int pos_x, int pos_y, int isRecursive) {

    if (grid->fields[pos_x][pos_y].marked == TRUE) {
        return UNDEFINED;
    }

    if (grid->fields[pos_x][pos_y].revealed == TRUE) {
        return UNDEFINED;
    } else if (grid->fields[pos_x][pos_y].mine == TRUE) {
        return LOSE;
    } else if (grid->fields[pos_x][pos_y].nearMines != 0) {
        if (isRecursive == FALSE) {
            grid->fields[pos_x][pos_y].revealed = TRUE;
            --grid->toReveal;
        }
        return UNDEFINED;
    } else {
        grid->fields[pos_x][pos_y].revealed = TRUE;
        --grid->toReveal;
        recursive_reveal(grid, pos_x, pos_y);
    }
    return UNDEFINED;
}

void recursive_reveal(GRID * grid, int pos_x, int pos_y) {
    int i, j;

    //Definindo minimos e maximos (em torno)
    int min_x = pos_x == 0 ? pos_x : pos_x - 1;
    int max_x = pos_x == grid->size - 1 ? pos_x : pos_x + 1;

    int min_y = pos_y == 0 ? pos_y : pos_y - 1;
    int max_y = pos_y == grid->size - 1 ? pos_y : pos_y + 1;

    // Percorre o entorno de acordo com os minimos e maximos encontrados.
    // Não visita os campos em posições diagonais.
    for (i = min_x; i <= max_x; ++i) {
        for (j = min_y; j <= max_y; ++j) {
            if (i == pos_x && j == pos_y) {
                continue;
            } else if ((i != min_x || i != max_x) && (j == min_y || j == max_y)) {
                rreveal(grid, i, j, TRUE);
            }
        }
    }
}
