#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <Arduino.h>

class SudokuGame {
  private:
    int **grid;
    bool **generated;
    int num_remove;
    bool is_solved = false;
    int MIN_NUM = 1;
    int MAX_NUM = 9;
    int SIZE = 9;
  public:
    SudokuGame(int);
    bool getSolvedState();
    void changeSolvedStated();
    void resetSolvedState();
    int getGridValue(int, int);
    int** getGridValues();
    bool isGenerated(int, int);
    void generateSudoku();
    void removeCells(int);
    bool solveSudoku();
    bool isSafe(int, int, int);
    bool isValueValid(int, int, int);
    void plus(int, int);
    void minus(int, int);
    bool** validateGrid();
    void reset();
    ~SudokuGame();
};

#endif