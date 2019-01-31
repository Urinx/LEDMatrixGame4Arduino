#include <arduino.h>
#include "joystick.h"

struct Direction get_direction(){
  /* Joystick
   *   X
   *  1023
   *   ^
   *   |
   *  509    0 <-- 520 --> 1023 Y
   *   |
   *   v
   *   0
   */
  int x = analogRead(STICK_X);
  int y = analogRead(STICK_Y);
  struct Direction dir;

  if(x < 200){
    dir.dx = -1;
  } else if(x > 800){
    dir.dx = 1;
  }

  if(y < 200){
    dir.dy = -1;
  } else if(y > 800){
    dir.dy = 1;
  }
  
  return dir;
}
