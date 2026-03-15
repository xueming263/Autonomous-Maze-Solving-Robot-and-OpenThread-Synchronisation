#include "pico/stdlib.h"
#include "motors.h"
#include "turn.h"

#define LEFT 'L'
#define STRAIGHT 'S'
#define RIGHT 'R'
#define UTURN 'B'

void execute_turn(char dir)
{
    switch (dir)
    {
    case 'L': // turn left
        motors_set_speeds(-600, 600);
        sleep_ms(540);
        break;
    case 'R': // turn right
        motors_set_speeds(600, -600);
        sleep_ms(540);
        break;
    case 'B': // turn round
        motors_set_speeds(600, -600);
        sleep_ms(1080);
        break;
    case 'S': // move straight forward
        break;
    }
    // move forward after turning out of intersection
    motors_set_speeds(500, 500);
}

char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right)
{
    if (found_left)
    {
        return LEFT; // left turn dominant
    }
    else if (found_straight)
    {
        return STRAIGHT; // move forward as secondary priority
    }
    else if (found_right)
    {
        return RIGHT; // turn right third priority
    }
    else
    {
        return UTURN; // last priority turn round
    }
}