#ifndef SUDOKU_GAME_H

#define SUDOKU_GAME_H

#define Y_MAX 9
#define X_MAX 9
#define MAX_CELL_NUMBER 9

#include <iostream>
#include <set>

namespace sudoku {

class Sudoku {
public:
    Sudoku();
    void printField();
    void solve();

private:
    struct Cell {
        int number = 0;
        std::set<int> potential_numbers;
    } field[Y_MAX][X_MAX];

    void fillPotentialNumbers();
    void getSquare(const int &y, const int &x, int &out_y, int &out_x);
    bool canBeInsertedInCell(int number_to_check, const int &y, const int &x);
    void editPotentialNumbers(int number_to_throw, const int &y, const int &x);
    bool fillCells();
    
};

}
// SUDOKU_GAME_H
#endif