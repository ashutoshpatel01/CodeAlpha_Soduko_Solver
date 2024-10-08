#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <vector>

class SudokuSolver {
public:
    bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num);
    bool solveSudoku(std::vector<std::vector<int>>& grid, int row, int col);
};

#endif // SUDOKU_SOLVER_H
