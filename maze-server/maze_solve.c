#include <stdio.h>
#include "pico/stdlib.h"
#include "ir_sensors.h"
#include "motors.h"
#include "maze_solve.h"
#include "follow_segment.h"
#include "path.h"
#include "turn.h"
#include "multi_display.h"
#include "sensors.h"
#include "display.h"

#define SIDE_SENSOR_THRESHOLD 400
#define MID_SENSORS_THRESHOLD 300
#define END_THRESHOLD 500

void maze_solve()
{
    while (1)
    {
        // stay on line using PD control and detect intersections

        follow_segment();

        //  excute if at an intersection
        if (is_intersection == 1)
        {
            // check if end point is reached
            unsigned char found_left = 0, found_straight = 0, found_right = 0;

            // run into intersection
            motors_set_speeds(500 , 500);

            // Check immediately if you have reached the destination
            refresh_sensor_values();
            if ((line_sensors_calibrated[0] >= END_THRESHOLD) 
            && (line_sensors_calibrated[1] >= END_THRESHOLD) 
            && (line_sensors_calibrated[2] >= END_THRESHOLD) 
            && (line_sensors_calibrated[3] >= END_THRESHOLD) 
            && (line_sensors_calibrated[4] >= END_THRESHOLD)) break;

            // Read sensor data and determine left and right paths within 50ms
            average_sensor_values();
            if (line_sensors_calibrated[0] >= SIDE_SENSOR_THRESHOLD) found_left = 1;
            if (line_sensors_calibrated[4] >= SIDE_SENSOR_THRESHOLD) found_right = 1;

            // Check the path directly ahead of the intersection within 50ms
            average_sensor_values();
            if ((line_sensors_calibrated[1] >= MID_SENSORS_THRESHOLD) 
            || (line_sensors_calibrated[2] >= MID_SENSORS_THRESHOLD) 
            || (line_sensors_calibrated[3] >= MID_SENSORS_THRESHOLD)) found_straight = 1;

            // Check again whether you have reached the end point
            refresh_sensor_values();
            if ((line_sensors_calibrated[0] >= END_THRESHOLD) 
            && (line_sensors_calibrated[1] >= END_THRESHOLD) 
            && (line_sensors_calibrated[2] >= END_THRESHOLD) 
            && (line_sensors_calibrated[3] >= END_THRESHOLD) 
            && (line_sensors_calibrated[4] >= END_THRESHOLD)) break;

            // If only a straight path is found and there is no path to the left or right, 
            // recursively perform maze pathfinding
            if (found_straight == 1 && found_left == 0 && found_right == 0) 
            {   
                is_intersection = 0;
                maze_solve();
            }

            // Steering according to left-hand preference
            unsigned char dir = select_turn(found_left, found_straight, found_right);

            // recorde path
            record_path(dir);
            sleep_ms(10);
            multi_display(path, 0, 0, COLOR_WHITE_ON_BLACK);

            // excute steering
            sleep_ms(50);
            execute_turn(dir);
            sleep_ms(100);
            is_intersection = 0;
        }
    }

    // stop motors
    motors_set_speeds(0, 0);
}
