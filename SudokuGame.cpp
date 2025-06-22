#include "SudokuGame.h"

SudokuGame::SudokuGame(int num_remove) : num_remove(num_remove) {
  this->grid = new int*[SIZE];
  this->generated = new bool*[SIZE];

  for (int i = 0; i < SIZE; ++i) {
    this->grid[i] = new int[SIZE];
    this->generated[i] = new bool[SIZE];
  }

  this->grid[SIZE][SIZE] = { 0 };
  this->generated[SIZE][SIZE] = { false };
}

bool SudokuGame::getSolvedState() {
  return this->is_solved;
}

void SudokuGame::changeSolvedStated() {
  this->is_solved = !this->is_solved; 
}

void SudokuGame::resetSolvedState() {
  this->is_solved = false;
}

int SudokuGame::getGridValue(int i, int j) {
  return this->grid[i][j];
}

int **SudokuGame::getGridValues() {
  return this->grid;
}

bool SudokuGame::isGenerated(int i, int j) {
  return this->generated[i][j];
}

void SudokuGame::generateSudoku() {
  this->reset();
  
  for (int i = 0; i < SIZE; i++) {
    int num = (i + random(SIZE)) % SIZE + 1;
    while (!isSafe(i, i, num)) {
      num = (num % SIZE) + 1;
    }
    this->grid[i][i] = num;
    this->generated[i][i] = true;
  }

  this->solveSudoku();
  if (num_remove == 0) changeSolvedStated(); 
  this->removeCells(num_remove);
}

void SudokuGame::removeCells(int numToRemove) {
  for (int i = 0; i < numToRemove; ++i) {
    int row = random(SIZE);
    int col = random(SIZE);
    this->grid[row][col] = 0;
    this->generated[row][col] = false;
  }
}

bool SudokuGame::solveSudoku() {
  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      if (this->grid[row][col] == 0) {
        for (int num = MIN_NUM; num <= MAX_NUM; num++) {
          if (isSafe(row, col, num)) {
            this->grid[row][col] = num;
            this->generated[row][col] = true;

            if (solveSudoku()) {
              return true;
            }

            this->grid[row][col] = 0;
            this->generated[row][col] = false;
          }
        }
        return false;
      }
    }
  }
  return true;
}

bool SudokuGame::isSafe(int row, int col, int num) {
  for (int x = 0; x < SIZE; x++)
    if (grid[row][x] == num || grid[x][col] == num)
      return false;

  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (this->grid[i + startRow][j + startCol] == num)
        return false;

  return true;
}

bool SudokuGame::isValueValid(int row, int col, int num) {
  if (num == 0) return false;

  for (int x = 0; x < SIZE; x++)
    if (
      (grid[row][x] == num && x != col) || 
      (grid[x][col] == num && x != row))
      return false;

  int startRow = row - row % 3;
  int startCol = col - col % 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (this->grid[i + startRow][j + startCol] == num &&
        (i + startRow != row) && (j + startCol != col))
        return false;
    }
  }

  return true;
}

void SudokuGame::plus(int i, int j) {
  if (this->isGenerated(i, j)) return;
  if (grid[i][j] >= MAX_NUM) grid[i][j] = MIN_NUM;
  else grid[i][j] += 1;
}

void SudokuGame::minus(int i, int j) {
  if (this->isGenerated(i, j)) return;
  if (this->grid[i][j] <= MIN_NUM) grid[i][j] = MAX_NUM;
  else this->grid[i][j] -= 1;
}

bool** SudokuGame::validateGrid() {
  bool **valid_check;

  valid_check = new bool* [SIZE];

  for (int i = 0; i < SIZE; ++i) {
    valid_check[i] = new bool[SIZE];
  }

  for (int row = 0; row < SIZE; ++row) {
    for (int col = 0; col < SIZE; ++col) {
      int value = this->getGridValue(row, col);
      bool is_valid = this->isValueValid(row, col, value);
      valid_check[row][col] = is_valid;
    }
  }

  return valid_check;
}

void SudokuGame::reset() {
  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      this->grid[row][col] = 0;
      this->generated[row][col] = false;
    }
  }
}

SudokuGame::~SudokuGame() {
  for (int i = 0; i < SIZE; ++i) {
    delete[] this->grid[i];
    delete[] this->generated[i];
  }
  delete[] this->grid;
  delete[] this->generated;
}