#include <Arduboy2.h>
Arduboy2 arduboy;
Sprites sprites;

#include "include/LinkedList.h"
#include "spr_title.h"
#include "spr_turtle.h"
#include "spr_grass_1.h"
#include "utils.h"

#define screen_width 128
#define screen_height 64

#define horizon_height 22
#define num_ripples 4.


enum rooms
{
    rm_menu,
    rm_game
};

unsigned int room = rm_menu;

unsigned int global_tick = 0;

int player_x;
int player_y;

int common_var = 0;

bool frame = false;

LinkedList<Object> objects = LinkedList<Object>();

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(60);
    common_var = 0;
}

void start_game()
{
    room = rm_game;
    player_x = screen_width * .5;
    player_y = screen_height * .75;
}

void instance_create(int x, int y, int type)
{
    Object obj = {type, x, y, 0.0};
    objects.add(obj);
}

void ripple(double percent)
{
    arduboy.drawFastHLine(0, horizon_height + (screen_height - horizon_height)*sq(sq(percent)), screen_width);
}

void draw_sprite(const uint8_t* frames[], int index, int number, int x, int y, bool centered = false, int w = 0, int h = 0)
{
    if (centered)
    {
        x -= w * .5;
        y -= h * .5;
    }

    sprites.drawPlusMask(x, y, frames[index % number], 0);
}

void loop()
{
    if (!arduboy.nextFrame())
        return;
    else
        global_tick += 1;

    arduboy.pollButtons();

    if (room == rm_menu)
    {
        if (common_var < 100)
            common_var += 1;
        else
            frame = true;

        arduboy.clear();

        draw_sprite(spr_title_frames, 0, 1, (1. - (common_var / 100.)) * -screen_width, 0);

        if (arduboy.justPressed(B_BUTTON) or arduboy.justPressed(A_BUTTON))
        {
            start_game();
        }
    }
    else if (room == rm_game)
    {
        if (arduboy.pressed(LEFT_BUTTON))
            player_x -= 1;

        if (arduboy.pressed(RIGHT_BUTTON))
            player_x += 1;

        player_x = max(1 + spr_turtle_width * .5, min(player_x, screen_width - spr_turtle_width * .5));

        arduboy.clear();

        // horizon
        arduboy.drawFastHLine(0, horizon_height, screen_width);

        for (int i = 0; i < num_ripples; i++)
        {
            ripple((double)((int)(global_tick * 0.5 + ((double)i * (1. / num_ripples) * 100.)) % 100) / 100.);
        }

        draw_sprite(spr_turtle_frames, global_tick * .4, spr_turtle_number, player_x, player_y, true, spr_turtle_width, spr_turtle_height);

    }

    if (frame)
    {
        // border
        arduboy.drawRect(0, 0, screen_width, screen_height);
    }

    arduboy.display();
}
