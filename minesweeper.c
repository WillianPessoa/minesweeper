#include "minesweeper.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1;
#define FALSE 0;

const char flag = '?';
const char notClicked = '*';

//EXEMPLO: Função defina neste arquivo. Veja "main.c".
void testFunction() {
   fprintf(stdout, "It's works!\n");
}

// Retorna
GRID * makeAGrid(int size, int bombs) {
    GRID * grid = malloc(sizeof(grid));

    // Atribui ao Grid o tamanho e a quantidade de bombas que este deve conter;
    grid->size = size;
    grid->bombs = bombs;

    // Constrói o grid;
    grid->grid = malloc(size * sizeof(FIELD*));

    int i, j;
    for (i = 0; i < size; ++i) {
        grid->grid[i] = malloc(size * sizeof(FIELD));

        // Atribui os valores padrões para cada campo;
        for (j = 0; j < size; ++j) {
            grid->grid[i][j].pos_x = i;
            grid->grid[i][j].pos_y = j;
            grid->grid[i][j].bomb = FALSE;
            grid->grid[i][j].marked = FALSE;
            grid->grid[i][j].revealed = FALSE;
            grid->grid[i][j].nearBombs = 0;
        }
    }
    return grid;
}

// Exibe o grid de acordo com o estado de cada campo.
void showGrid(GRID * grid) {
    int i, j;

    fprintf(stdout, "\n***************** GRID *****************\n\n");

    for (i = 0; i < grid->size; ++i) {
        for (j = 0; j < grid->size; ++j) {

            // Se o campo estiver marcado, exibe a sinalização de marcação;
            if (grid->grid[i][j].marked) {
                fprintf(stdout, "[%c] ", flag);
            }

            // Se o campo já foi revelado...;
            else if (grid->grid[i][j].revealed) {

                //... e se o campo possuir bombas próximas, exibe a quantidade;
                if(grid->grid[i][j].nearBombs != 0) {
                    fprintf(stdout, "[%d] ", grid->grid[i][j].nearBombs);
                }
                //... e se não possuir bombas próximas, exibe a sinalização de um campo vazio;
                else {
                    fprintf(stdout, "[ ] ");
                }
            }

            //Se não tiver sido clicado, exibe a sinalização de não clicado.
            else {
                fprintf(stdout, "[%c] ", notClicked);
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
