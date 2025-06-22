#include "GoGame.h"

GoGame::GoGame() {
  this->board = new int*[SIZE];
  for (int i = 0; i < SIZE; ++i) {
    this->board[i] = new int[SIZE];
  }

  this->board[SIZE][SIZE] = { EMPTY };
  this->current_player = PLAYER1;
}

void GoGame::reset() {
  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      board[row][col] = EMPTY;
    }
  }
  this->current_player = PLAYER1;
}

int GoGame::getCurrentPlayer() {
  return this->current_player;
}

int GoGame::getPreviousPlayer() {
  return (this->current_player == PLAYER1 ? PLAYER2 : PLAYER1);
}

int** GoGame::getBoard() {
  return this->board;
}

bool GoGame::isValid(int row, int col) {
  return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

void GoGame::dfs(bool** visited, int x, int y, int player, int* capturedStonesX, int* capturedStonesY, int& count) {
  static const int dx[] = {0, 1, 0, -1};
  static const int dy[] = {-1, 0, 1, 0};

  visited[x][y] = true;
  capturedStonesX[count] = x;
  capturedStonesY[count] = y;
  count++;

  for (int i = 0; i < 4; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (isValid(nx, ny) && !visited[nx][ny]) {
      if (board[nx][ny] == 0) {
        count = 0;
      } else if (board[nx][ny] == player) {
        dfs(visited, nx, ny, player, capturedStonesX, capturedStonesY, count);
      }
    }
  }
}

void GoGame::checkCapturedGroups(int player) {
  bool** visited = new bool*[SIZE];
  int* captureStonesX = new int[SIZE * SIZE];
  int* captureStonesY = new int[SIZE * SIZE];

  for (int i = 0; i < SIZE; i++) {
    visited[i] = new bool[SIZE];
  }

  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      visited[row][col] = false;
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (!visited[i][j] && board[i][j] == player) {
        int count = 0;
        dfs(visited, i, j, player, captureStonesX, captureStonesY, count);

        if (count > 0) {
          // Serial.print("Captured stones by player " + String(player));
          for (int k = 0; k < count; ++k) {
            board[captureStonesX[k]][captureStonesY[k]] = EMPTY;
            // Serial.print("(" + String(captureStonesX[k]) + "," + String(captureStonesY[k]) + ") ");
          }
        }
      }
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    delete[] visited[i];
  }
  delete[] visited;
  delete[] captureStonesX;
  delete[] captureStonesY;
}

bool GoGame::makeMove(int i, int j) {
  if (this->board[i][j] != EMPTY) return false;
  this->board[i][j] = this->current_player;
  this->changeTurn();
  return true;
}

void GoGame::changeTurn() {
  this->current_player = (this->current_player == PLAYER1 ? PLAYER2 : PLAYER1);
}

GoGame::~GoGame() {
  for (int i = 0; i < SIZE; ++i) {
    delete[] board[i];
  }
  delete[] board;
}

