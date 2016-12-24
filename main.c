#include <stdio.h>
#include "minesweeper.h"

int main()
{
    //EXEMPLO: Função sendo chamada e funcionando.
    testFunction();

    GRID * grid = makeAGrid(10, 0);

    showGrid(grid);

    plantMinesIn(grid, 30);

    showGridRevelead(grid);
    return 0;
}
