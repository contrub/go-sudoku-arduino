// #ifndef ANALOG_STICK_H
// #define ANALOG_STICK_H

#include <Arduino.h>

class AnalogStick {
  private:
    uint8_t VERT_PIN;
    uint8_t HORZ_PIN;
    uint8_t SEL_PIN;
    int i_choice;
    int j_choice;
    int MAX = 8;
    int MIN = 0;
  public:
    AnalogStick(uint8_t, uint8_t, uint8_t);
    void getStickPos(int&, int&); 
    void resetPos();
    bool move_stick();
};