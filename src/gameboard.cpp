#include <Arduino.h>
#include "gameboard.h"

void Serial_Gameboard::clear_terminal() const
{
  constexpr char vt102_clear_cmd[4] =
    { 0x1B, '[', '2', 'J' }; // `Esc[2J`

  Serial.write(vt102_clear_cmd, 4);
}
