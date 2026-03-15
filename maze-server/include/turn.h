#ifndef TURN_H
#define TURN_H

/**
 * Excute steering maneuvers
 *
 * @param dir steering direction, values can be:
 *            'L' - turn left
 *            'R' - turn right
 *            'B' - turn round
 *            'S' - move forward (without turn)
 */
void execute_turn(char dir);

char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right);

#endif // TURN_H