#include <Arduboy2.h>
#include "spr_turtle.h"

#define screen_width 128
#define screen_height 64

#define horizon_height 22

Arduboy2 arduboy;
Sprites sprites;

unsigned int global_tick = 0;

int player_x = screen_width * .5;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void ripple(double percent)
{
  arduboy.drawFastHLine(0, horizon_height + (screen_height - horizon_height)*sq(sq(percent)), screen_width);
}

void draw_sprite( uint8_t* frames[], int index, int number, int x, int y, bool centered = false, int w = 0, int h = 0)
{
  if (centered)
  {
    x -= w * .5;
    y -= h * .5;
  }

  index = index % number;

  sprites.drawPlusMask(x, y, frames[index], 0);
}

void loop()
{
  if (!arduboy.nextFrame())
    return;
  else
    global_tick += 1;

  if (arduboy.pressed(LEFT_BUTTON))
    player_x -= 1;

  if (arduboy.pressed(RIGHT_BUTTON))
    player_x += 1;

  player_x = max(1 + spr_turtle_width * .5, min(player_x, screen_width - spr_turtle_width * .5));

  arduboy.clear();

  // horizon
  arduboy.drawFastHLine(0, horizon_height, screen_width);

  ripple((double)((global_tick + 00) % 100) / 100.);
  ripple((double)((global_tick + 25) % 100) / 100.);
  ripple((double)((global_tick + 50) % 100) / 100.);
  ripple((double)((global_tick + 75) % 100) / 100.);

  draw_sprite(spr_turtle_frames, global_tick * .4, spr_turtle_number, player_x, screen_height * .75, true, spr_turtle_width, spr_turtle_height);

  // border
  arduboy.drawRect(0, 0, screen_width, screen_height);

  arduboy.display();
}
