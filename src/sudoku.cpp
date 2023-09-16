#include "../include/sudoku.h"
#define LOG(x) std::cout << x << " ";
#define LOGLN(x) std::cout << x << std::endl;

sudoku::Sudoku::Sudoku() {
    std::cout << "Enter number filled into cell or enter 0 instead this number:" << std::endl;
    for (int y = 0; y < Y_MAX; y++) {
        for (int x = 0; x < X_MAX; x++)
            std::cin >> field[y][x].number;
        std::cout << "filled entire row" << std::endl;
    }
}

void sudoku::Sudoku::printField() {
    for (int y = 0; y < Y_MAX; y++) {
        for (int x = 0; x < X_MAX; x++)
            std::cout << field[y][x].number << " ";
        std::cout << std::endl;
    }
}

void sudoku::Sudoku::solve() {
    // TODO: add checking field before solving 
    bool not_solved = true;
    fillPotentialNumbers();
    
    while (not_solved) {
        not_solved = fillCells();
        fillPotentialNumbers();
    }
}

void sudoku::Sudoku::fillPotentialNumbers() {
    for (int y = 0; y < Y_MAX; y++) {
        for (int x = 0; x < X_MAX; x++) {
            if (field[y][x].number == 0) {
                for (int i = 1; i <= MAX_CELL_NUMBER; i++) {
                    if (canBeInsertedInCell(i, y, x)) {
                        field[y][x].potential_numbers.insert(i);
                    }
                }
            }
        }
    }
}

void sudoku::Sudoku::getSquare(const int &y, const int &x, int &out_y, int &out_x) {
    if (x < 3)      { out_x = 0; }
    else if (x < 6) { out_x = 3; }
    else                { out_x = 6; }

    if (y < 3)      { out_y = 0; }
    else if (y < 6) { out_y = 3; }
    else                { out_y = 6; }
}

bool sudoku::Sudoku::canBeInsertedInCell(int number_to_check, const int &y, const int &x) {
    // row checks
    for (int row_checker_x = 0; row_checker_x < X_MAX; row_checker_x++) {
        if (field[y][row_checker_x].number == number_to_check) { return false; }
    }
    // collumn checks
    for (int row_checker_y = 0; row_checker_y < Y_MAX; row_checker_y++) {
        if (field[row_checker_y][x].number == number_to_check) { return false; }
    }

    // square checks
    int square_begin_y,
        square_begin_x;
    getSquare(y, x, square_begin_y, square_begin_x);
    for (int y = square_begin_y; y < square_begin_y + 3; y++) {
        for (int x = square_begin_x; x < square_begin_x + 3; x++) {
            if (field[y][x].number == number_to_check) { return false; }
        }
    }
    return true;
}

void sudoku::Sudoku::editPotentialNumbers(int number_to_throw, const int &y, const int &x) {
    // row erase
    for (int row_checker_x = 0; row_checker_x < X_MAX; row_checker_x++) {
        if (field[y][row_checker_x].potential_numbers.contains(number_to_throw)) {
            field[y][row_checker_x].potential_numbers.erase(number_to_throw);
        }
    }
    // collumn erase
    for (int row_checker_y = 0; row_checker_y < Y_MAX; row_checker_y++) {
        if (field[row_checker_y][x].potential_numbers.contains(number_to_throw)) {
            field[row_checker_y][x].potential_numbers.erase(number_to_throw);
        }
    }
    // square erase
    int square_begin_y,
        square_begin_x;
    getSquare(y, x, square_begin_y, square_begin_x);

    for (int y = square_begin_y; y < square_begin_y + 3; y++) {
        for (int x = square_begin_x; x < square_begin_x + 3; x++) {
            field[y][x].potential_numbers.erase(number_to_throw);
        }
    }
}

bool sudoku::Sudoku::fillCells() {
    bool cells_filled = false;
    
    for (int y = 0; y < Y_MAX; y++) {
        for (int x = 0; x < X_MAX; x++) {
            if (field[y][x].potential_numbers.size() == 1) {
                int a = 0;
                for (int i = 1; i <= MAX_CELL_NUMBER; i++) {
                    if (field[y][x].potential_numbers.contains(i)) {
                        a = i;
                        break;
                    }
                }
                field[y][x].number = a;
                editPotentialNumbers(a, y, x);
                cells_filled = true;
            }
        }
    }
    return cells_filled;
}
