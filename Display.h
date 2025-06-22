// #ifndef DISPLAY_H
// #define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_ILI9341.h> 

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class Display : public Adafruit_ILI9341 {
	public:
		Display(uint8_t, uint8_t);
    void clear();
    // SUDOKU
    void writeSudokuMsg();
    void writeSudokuWin();
    void convertSudokuCoords(int, int, int&, int&);
    void drawSudokuGrid(int**);
    void backlightSudokuValue(int, int, int);
    void updateSudokuValue(int, int, int);
    void clearSudokuValue(int, int);
    void drawSudokuChoice(int, int);
    void clearSudokuChoice(int, int);
    // GO
    void writeGoMsg();
    void convertGoCoords(int i, int j, int &x, int &y);
    void drawGoBorders();
    void drawGoMove(int, int, int);
    void drawGoBoard(int**);
    void drawPlayerPoints();
    void drawPlayerPoint(int);
    void drawChoice(int, int);
    void clearPlayerPoint(int);
    void drawGoChoice(int, int);
    void clearGoChoice(int, int);
};