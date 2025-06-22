// #include "SPI.h"

const int8_t VERT_PIN = A0;
const int8_t HORZ_PIN = A1;
const int8_t SEL_PIN = 2;

const uint8_t GREEN_BTN = 3;
const uint8_t RED_BTN = 4;
const uint8_t BLUE_BTN = 5;
const uint8_t SLIDE_SWITCH = 6;

const uint8_t TFT_DC = 9;
const uint8_t TFT_CS = 10;

#include "Display.h"
#include "SudokuGame.h"
#include "AnalogStick.h"
#include "GoGame.h"

AnalogStick analogStick(VERT_PIN, HORZ_PIN, SEL_PIN);
Display display(TFT_CS, TFT_DC);
SudokuGame sudoku(20);
GoGame go;

bool sudokuDrawn = false;
bool goDrawn = false;
int i = 0, j = 0, x, y;

void resetVars() {
  i = 0;
  j = 0;
}

void setup() {
  Serial.begin(9600);

  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);
  pinMode(BLUE_BTN, INPUT_PULLUP);
  pinMode(SLIDE_SWITCH, INPUT_PULLUP);

  display.begin();
}

void loop() {
  int switch_state = digitalRead(SLIDE_SWITCH);

  switch (switch_state) {
    case 0:
      sudokuGame();
      break;
    case 1:
      goGame();
      break;
  }
}


void goGame() {
  if (!goDrawn) {
    display.clear();
    display.writeGoMsg();

    go.reset();
    display.drawGoBorders();
    display.drawPlayerPoints();
    resetVars();
    analogStick.resetPos();
    display.convertGoCoords(i, j, x, y);
    display.drawGoChoice(x, y);

    display.drawPlayerPoint(1);

    goDrawn = true;
    sudokuDrawn = false;
  }

  if (analogStick.move_stick()) {
    display.clearGoChoice(x, y);
    analogStick.getStickPos(i, j);
    display.convertGoCoords(i, j, x, y);
    display.drawGoChoice(x, y);
  }

  if (digitalRead(GREEN_BTN) == LOW) {
    bool move = go.makeMove(i, j);
    int curr_player = go.getCurrentPlayer();
    int prev_player = go.getPreviousPlayer();

    if (curr_player == 1 && move) {
      display.clearPlayerPoint(prev_player);
      display.drawPlayerPoint(curr_player);
      go.checkCapturedGroups(curr_player);
    } else if (move) {
      display.clearPlayerPoint(prev_player);
      display.drawPlayerPoint(curr_player);
      go.checkCapturedGroups(curr_player);
    }

    int** board = go.getBoard();
    display.drawGoBoard(board);
  }

  if (digitalRead(RED_BTN) == LOW) {
    int curr_player = go.getCurrentPlayer();
    int prev_player = go.getPreviousPlayer();
    go.changeTurn();
    display.clearPlayerPoint(curr_player);
    display.drawPlayerPoint(prev_player);
  }

  if (digitalRead(BLUE_BTN) == LOW) {
    goDrawn = false;
  }

  delay(300);
}

void sudokuGame() {
  if (!sudokuDrawn) {
    display.clear();
    display.writeSudokuMsg();

    sudoku.resetSolvedState();
    sudoku.generateSudoku();
    resetVars();
    analogStick.resetPos();
    display.drawSudokuGrid(sudoku.getGridValues());
    display.convertSudokuCoords(i, j, x, y);
    display.drawSudokuChoice(x, y);

    goDrawn = false;
    sudokuDrawn = true;
  }

  if (analogStick.move_stick()) {
    display.clearSudokuChoice(x, y);
    analogStick.getStickPos(i, j);
    display.convertSudokuCoords(i, j, x, y);
    display.drawSudokuChoice(x, y);
  }

  if (digitalRead(GREEN_BTN) == LOW) {
    if (sudoku.isGenerated(i, j)) return;
    sudoku.plus(i, j);
    display.updateSudokuValue(sudoku.getGridValue(i, j), i, j);
  }

  if (digitalRead(RED_BTN) == LOW) {
    if (sudoku.isGenerated(i, j)) return;
    sudoku.minus(i, j);
    display.updateSudokuValue(sudoku.getGridValue(i, j), i, j);
  }

  if (digitalRead(BLUE_BTN) == LOW) {
    bool** checks = sudoku.validateGrid();
    int bad_check_count = 0;
    int value;

    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        if (!checks[row][col] && !sudoku.isGenerated(row, col)) {
          bad_check_count++;
          value = sudoku.getGridValue(row, col); 
          display.backlightSudokuValue(value, row, col);
        }
      }
    }

    if (bad_check_count == 0) {
      sudoku.changeSolvedStated();
      display.writeSudokuWin();
      sudokuDrawn = false;
      delay(2000);
      return;
    }

    delay(1000);

    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        if (!checks[row][col] && !sudoku.isGenerated(row, col)) {
          value = sudoku.getGridValue(row, col); 
          display.updateSudokuValue(value, row, col);
        }
      }
    }
  }

  delay(300);
}