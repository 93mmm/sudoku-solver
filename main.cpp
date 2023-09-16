#include <iostream>
#include "include/sudoku.h"

int main() {
    sudoku::Sudoku game;
    game.solve();
    game.printField();
    return 0;
}
// TODO: read field from file