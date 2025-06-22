#ifndef GO_GAME_H
#define GO_GAME_H

#include <Arduino.h>

class GoGame {
  private:
    int **board;
    int current_player;
    int EMPTY = 0;
    int PLAYER1 = 1;
    int PLAYER2 = 2;
    int SIZE = 9;
  public:
    GoGame();
    void reset();
    int getCurrentPlayer();
    int getPreviousPlayer();
    int** getBoard();
    bool isValid(int, int);
    void dfs(bool**, int, int, int, int*, int*, int&);
    void checkCapturedGroups(int);
    bool makeMove(int, int);
    void changeTurn();
    ~GoGame();
};

#endif