#include "Display.h"

Display::Display(uint8_t cs_pin, uint8_t ds_pin) :
  Adafruit_ILI9341(cs_pin, ds_pin) { }

void Display::clear() {
  this->fillScreen(BLACK);
}

// SUDOKU

void Display::writeSudokuMsg() {
  setTextSize(2);
  setTextColor(CYAN);
  setCursor(60, 20);
  print("SUDOKU GAME");
}

void Display::writeSudokuWin() {
  setTextSize(2);
  setTextColor(GREEN);
  setCursor(25, 290);
  print("PUZZLE COMPLETED");
}

void Display::convertSudokuCoords(int i, int j, int &x, int &y) {
  x = 14 + 80 * (j / 3) + 20 * (j % 3);
  y = 60 + 80 * (i / 3) + 20 * (i % 3);
}

void Display::drawSudokuGrid(int **board) {
  int x, y;
  setTextColor(WHITE);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) continue;
      convertSudokuCoords(i, j, x, y);
      setTextSize(2);
      setCursor(x, y);
      print(board[i][j]);
      drawRect(x - 2, y - 2, 14, 18, BLACK);
    }
  }
}

void Display::backlightSudokuValue(int value, int i, int j) {
  int x, y;
  convertSudokuCoords(i, j, x, y);
  clearSudokuValue(x, y);
  setCursor(x, y);
  setTextColor(RED);
  print(value);
}

void Display::updateSudokuValue(int value, int i, int j) {
  int x, y;
  convertSudokuCoords(i, j, x, y);
  clearSudokuValue(x, y);
  setCursor(x, y);
  setTextColor(GREEN);
  print(value);
}

void Display::clearSudokuValue(int x, int y) {
  this->fillRect(x - 1, y - 1, 12, 16, BLACK);
}

void Display::drawSudokuChoice(int x, int y) {
  this->drawRect(x - 2, y - 2, 14, 18, RED);
}

void Display::clearSudokuChoice(int x, int y) {
  this->drawRect(x - 2, y - 2, 14, 18, BLACK);
}

// GO

void Display::writeGoMsg() {
  setTextSize(2);
  setTextColor(CYAN);
  setCursor(80, 20);
  print("GO GAME");
}

void Display::convertGoCoords(int i, int j, int &x, int &y) {
  x = 30 + 20 * j;
  y = 81 + 20 * i;
}

void Display::drawGoBoard(int** board) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (board[row][col] == 0) {
        this->drawGoMove(row, col, BLACK);
      } else if (board[row][col] == 1) {
        this->drawGoMove(row, col, GREEN);
      } else if (board[row][col] == 2) {
        this->drawGoMove(row, col, MAGENTA);
      }
    }
  }
}

void Display::drawGoMove(int i, int j, int color) {
  int x, y;
  this->convertGoCoords(i, j, x, y);

  this->drawCircle(x + 8, y + 9, 5, color);
  this->fillCircle(x + 8, y + 9, 5, color);
}

void Display::drawGoBorders() {
  this->drawRect(27, 78, 182, 182, YELLOW);
}

void Display::drawPlayerPoints() {
  this->drawCircle(120, 280, 5, GREEN);
  this->fillCircle(120, 280, 5, GREEN);
  this->drawCircle(120, 300, 5, MAGENTA);
  this->fillCircle(120, 300, 5, MAGENTA);
}

void Display::drawPlayerPoint(int player) {
  this->drawLine(85, 260 + (player * 20), 100, 260 + (player * 20), WHITE);
  this->drawLine(94, 257 + (player * 20), 100, 260 + (player * 20), WHITE);
  this->drawLine(94, 263 + (player * 20), 100, 260 + (player * 20), WHITE);
}

void Display::clearPlayerPoint(int player) {
  this->drawLine(85, 260 + (player * 20), 100, 260 + (player * 20), BLACK);
  this->drawLine(94, 257 + (player * 20), 100, 260 + (player * 20), BLACK);
  this->drawLine(94, 263 + (player * 20), 100, 260 + (player * 20), BLACK);
}

void Display::drawGoChoice(int x, int y) {
  this->drawRect(x, y, 18, 18, RED);
}

void Display::clearGoChoice(int x, int y) {
  this->drawRect(x, y, 18, 18, BLACK);
}