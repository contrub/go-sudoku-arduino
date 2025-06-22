#include "AnalogStick.h"

AnalogStick::AnalogStick(uint8_t vert_pin, uint8_t horz_pin, uint8_t sel_pin) :
  VERT_PIN(vert_pin), HORZ_PIN(horz_pin), SEL_PIN(sel_pin)
{
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);
}

void AnalogStick::getStickPos(int &i_pos, int &j_pos) {
  i_pos = this->i_choice;
  j_pos = this->j_choice;
}

void AnalogStick::resetPos() {
  this->i_choice = 0;
  this->j_choice = 0;
}

bool AnalogStick::move_stick() {
  int horz = analogRead(HORZ_PIN);
  int vert = analogRead(VERT_PIN);
  bool move = false;

  if (vert < 300) {
    if (i_choice < this->MAX) this->i_choice += 1;
    move = true;
  }
  if (vert > 700) {
    if (i_choice > this->MIN) this->i_choice -= 1;
    move = true;
  }
  if (horz < 300) {
    if (j_choice < this->MAX) this->j_choice += 1;
    move = true;
  }
  if (horz > 700) {
    if (j_choice > this->MIN) this->j_choice -= 1;
    move = true;
  }

  return move;
}