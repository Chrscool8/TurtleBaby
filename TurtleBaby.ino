#include <Arduboy2.h>
#include "spr_turtle.h"

#define screen_width 128
#define screen_height 64

#define horizon_height 32

Arduboy2 arduboy;
Sprites sprites;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(10);
}

void loop()
{
  if (!arduboy.nextFrame())
    return;

  arduboy.clear();

  // border
  arduboy.drawRect(0, 0, screen_width, screen_height);

  // horizon
  arduboy.drawFastHLine(0, horizon_height, screen_width);

  arduboy.display();
}
