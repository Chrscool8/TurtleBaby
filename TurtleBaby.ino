#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;

#include "include/LinkedList.h"
#include "spr_title.h"
#include "spr_turtle.h"
#include "spr_grass_1.h"
#include "spr_coin.h"
#include "utils.h"
#include "audio.h"

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

int score = 0;

int game_speed = 1;

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
    frame = true;

    score = 0;

    randomSeed(analogRead(0));

    sound.tones(msc_totalth);
}

void instance_create(int type, int x, int y)
{
    Object obj;
    obj.object_type = type;
    obj.x = x;
    obj.y = y;
    obj.percent = 0.0;
    objects.add(obj);
}

int percent_height_function(double percent)
{
    return horizon_height + (screen_height - horizon_height) * (percent * percent * percent);
}

void ripple(double percent)
{
    arduboy.drawFastHLine(0, percent_height_function(percent), screen_width);
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

        if (arduboy.everyXFrames(73))
            instance_create(obj_grass_1, random(10, screen_width - 10), horizon_height);

        if (arduboy.everyXFrames(102))
            instance_create(obj_coin, random(10, screen_width - 10), horizon_height);

        arduboy.clear();

        arduboy.setCursor(3, 3);
        arduboy.write("Turtcoins: ");
        arduboy.write(String(score).c_str());
        arduboy.write("   ");
        arduboy.write(String(game_speed).c_str());

        // horizon
        arduboy.drawFastHLine(0, horizon_height, screen_width);

        for (int i = 0; i < num_ripples; i++)
        {
            ripple((double)((int)(global_tick * 0.5 + ((double)i * (1. / num_ripples) * 100.)) % 100) / 100.);
        }

        for (int i = 0; i < objects.size(); i++)
        {
            Object current = objects.get(i);
            switch (current.object_type)
            {
                case obj_grass_1:

                    current.percent += .005 * game_speed;
                    current.y = percent_height_function(current.percent) ;

                    if (current.percent < .5)
                        draw_sprite(spr_grass_1_small_frames, 0, spr_grass_1_number, current.x, current.y - spr_grass_1_height);
                    else
                        draw_sprite(spr_grass_1_frames, 0, spr_grass_1_number, current.x, current.y - spr_grass_1_height);

                    if (current.y > screen_height + spr_grass_1_height)
                    {
                        objects.remove(i);
                        i -= 1;
                    }
                    else
                    {
                        objects.set(i, current);
                    }

                    break;

                case obj_coin:

                    current.percent += .005 * game_speed;
                    current.y = percent_height_function(current.percent) ;

                    draw_sprite(spr_coin_frames, current.percent * 16., spr_coin_number, current.x, current.y - spr_coin_height);

                    // collide with turtle
                    if ((current.y > screen_height - spr_turtle_height * .5) && abs((current.x + spr_coin_width * .5) - (player_x)) < spr_turtle_width * .5)
                    {
                        objects.remove(i);
                        i -= 1;
                        score += 1;
                    }
                    // off screen
                    else if (current.y > screen_height + spr_coin_height)
                    {
                        objects.remove(i);
                        i -= 1;
                        score -= 1;
                    }
                    // normal movement step
                    else
                    {
                        objects.set(i, current);
                    }

                    break;

                default: break;
            }
        }

        game_speed = max(1, floor(score / 10.));

        draw_sprite(spr_turtle_frames, global_tick * .4, spr_turtle_number, player_x, player_y, true, spr_turtle_width, spr_turtle_height);
    }

    if (frame)
    {
        // border
        arduboy.drawRect(0, 0, screen_width, screen_height);
    }

    arduboy.display();
}
