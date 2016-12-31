#ifndef MENU_H
#define MENU_H

typedef struct _GRID GRID; // Forward declaration

void launchMenu(GRID *grid);

void mainMenu(int * mainOp);

void setupMenu(int * size, int * mines);

void defSizeMenu(int * size);

void defMinesMenu(int * mines, int * size);

#endif // MENU_H
