#include "minesweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

const char flag = '?';
const char notClicked = '*';
const char mined = 'M';

//EXEMPLO: Função defina neste arquivo. Veja "main.c".
void testFunction() {
   fprintf(stdout, "It's works!\n");
}

// Retorna
GRID * makeAGrid(int size, int mines) {
    GRID * grid = malloc(sizeof(grid));

    // Atribui ao Grid o tamanho e a quantidade de bombas que este deve conter;
    grid->size = size;
    grid->mines = mines;

    // Constrói o grid;
    grid->fields = malloc(size * sizeof(FIELD*));

    int i, j;
    for (i = 0; i < size; ++i) {
        grid->fields[i] = malloc(size * sizeof(FIELD));

        // Atribui os valores padrões para cada campo;
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
        for (j = 0; j < grid->size; ++j) {

            // Se o campo estiver marcado, exibe a sinalização de marcação;
            if (grid->fields[i][j].marked) {
                fprintf(stdout, "[%c]", flag);
            }

            // Se o campo já foi revelado...;
            else if (grid->fields[i][j].revealed) {

                //... e se o campo possuir bombas próximas, exibe a quantidade;
                if(grid->fields[i][j].nearMines != 0) {
                    fprintf(stdout, "[%d] ", grid->fields[i][j].nearMines);
                }
                //... e se não possuir bombas próximas, exibe a sinalização de um campo vazio;
                else {
                    fprintf(stdout, "[ ]");
                }
            }

            //Se não tiver sido clicado, exibe a sinalização de não clicado.
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
        for (j = 0; j < grid->size; ++j) {

            if (grid->fields[i][j].mine == TRUE) {
                fprintf(stdout, "[%c]", mined);
            }
            else if (grid->fields[i][j].nearMines != 0) {
                fprintf(stdout, "[%d]", grid->fields[i][j].nearMines);
            }
            else {
                fprintf(stdout, "[ ]");
            }
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

// Planta a quantidade de minas no grid aleatoriamente.
void plantMinesIn(GRID *grid, int minesToPlant) {
    srand(time(NULL));

    int size = grid->size;

    int pos_x;
    int pos_y;

    int minesPlanted;

    for (minesPlanted = 0; minesPlanted < minesToPlant; ++minesPlanted) {
        pos_x = rand() % size;
        pos_y = rand() % size;

        if (grid->fields[pos_x][pos_y].mine == FALSE) {
            grid->fields[pos_x][pos_y].mine = TRUE;
            setNearMinesAround(&grid->fields[pos_x][pos_y], grid);
        }
        else {
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
    int min_x = field->pos_x == 0 ? field->pos_x : field->pos_x-1;
    int max_x = field->pos_x == grid->size-1 ? field->pos_x :field->pos_x+1;

    int min_y = field->pos_y == 0 ? field->pos_y : field->pos_y-1;
    int max_y = field->pos_y == grid->size-1 ? field->pos_y :field->pos_y+1;

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

    //Definindo minimos e máximos
    int min_x = field->pos_x == 0 ? field->pos_x : field->pos_x-1;
    int max_x = field->pos_x == grid->size-1 ? field->pos_x :field->pos_x+1;

    int min_y = field->pos_y == 0 ? field->pos_y : field->pos_y-1;
    int max_y = field->pos_y == grid->size-1 ? field->pos_y :field->pos_y+1;

    //Percorre o entorno de acordo com os mínimos e máximos encontrados.
    for (i = min_x; i <= max_x; ++i) {
        for (j = min_y; j <=max_y; ++j) {
            if (i == field->pos_x && j == field->pos_y) {
                continue;
            }
            // e incrementa o "nearBombs" de cada um.
            ++grid->fields[i][j].nearMines;
        }
    }
}



void clickIn(int pos_x, int pos_y, GRID * grid, char typeOfClick){

	puts("Digite a linha e a coluna da posi��o que deseja clicar:");

	scanf("%d %d" ,&grid->fields[pos_x][pos_y]);

	puts("Digite 'O' para revelar o campo e 'M' para marcar o campo: ")
	scanf("%c", &typeOfClick);

	switch (typeOfClick){
	
	case M:
		grid->fields[pos_x][pos_y].marked=TRUE;


	case O:

		if (grid->fields[pos_x][pos_y].mine==TRUE){

			puts("GAME OVER!");

			break;
		}else{

			if (grid->fields[pos_x][pos_y].nearMines>0){

				grid->fields[pos_x][pos_y].revealed=TRUE;

			}else if (grid->fields[pos_x][pos_y].nearMines==0){
				
				...
			}			
		}		
	}
						
}



