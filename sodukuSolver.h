#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <iostream>
#include <vector>

class SudokuSolver {
private:
    std::vector<std::vector<int>> grid;

    bool isSafe(int row, int col, int num) {
        // Check if num is not in the current row and column
        for (int x = 0; x < 9; x++) {
            if (grid[row][x] == num || grid[x][col] == num) {
                return false;
            }
        }

        // Check if num is not in the current 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    bool solveSudoku() {
        int row, col;
        if (!findUnassignedLocation(row, col)) {
            return true; // Success
        }

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solveSudoku()) {
                    return true;
                }

                grid[row][col] = 0; // Failure, undo & try again
            }
        }

        return false; // Trigger backtracking
    }

    bool findUnassignedLocation(int &row, int &col) {
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    SudokuSolver(const std::vector<std::vector<int>> &inputGrid) {
        grid = inputGrid;
    }

    void solve() {
        if (solveSudoku()) {
            printGrid();
        } else {
            std::cout << "No solution exists" << std::endl;
        }
    }

    void printGrid() const {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                std::cout << grid[row][col] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // SUDOKU_SOLVER_H
