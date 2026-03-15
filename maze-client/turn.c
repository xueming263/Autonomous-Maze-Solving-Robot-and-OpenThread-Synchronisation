#include "pico/stdlib.h"
#include "motors.h"
#include "turn.h"
#include "path.h"

#define LEFT 'L'
#define STRAIGHT 'S'
#define RIGHT 'R'
#define UTURN 'B'

void execute_turn(int index)
{
    char command_i = path[index];
    switch (command_i)
    {
    case 'L': // turn left
        motors_set_speeds(-600, 600);
        sleep_ms(540);
        break;
    case 'R': // turn right
        motors_set_speeds(600, -600);
        sleep_ms(540);
        break;
    case 'S': // move forward
        // means ignore at the intersection
        break;
    }
    // stop motors
    motors_set_speeds(0, 0);
}
