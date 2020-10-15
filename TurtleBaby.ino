#include <Arduboy2.h>
#include "spr_turtle.h"

#define screen_width 128
#define screen_height 64

#define horizon_height 32

Arduboy2 arduboy;
Sprites sprites;

unsigned int global_tick = 0;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void ripple(double percent)
{
  arduboy.drawFastHLine(0, horizon_height + (screen_height - horizon_height)*sq(sq(percent)), screen_width);
}

void loop()
{
  if (!arduboy.nextFrame())
    return;
  else
    global_tick += 1;

  arduboy.clear();

  // border
  arduboy.drawRect(0, 0, screen_width, screen_height);

  // horizon
  arduboy.drawFastHLine(0, horizon_height, screen_width);

  ripple((double)((global_tick + 00) % 100) / 100.);
  ripple((double)((global_tick + 33) % 100) / 100.);
  ripple((double)((global_tick + 66) % 100) / 100.);

  arduboy.display();
}
