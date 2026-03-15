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

#define SIDE_SENSOR_THRESHOLD 400
#define MID_SENSORS_THRESHOLD 300
#define END_THRESHOLD 500

void maze_solve()
{
    int current_intersection = 0;

    while (1)
    {
        // stay on line using PD control and detect intersections

        follow_segment();

        // excute if at an intersection
        //if (false)
        if (is_intersection == 1)
        {

            // check if end point is reached
            refresh_sensor_values();
            if ((line_sensors_calibrated[0] >= END_THRESHOLD) 
            && (line_sensors_calibrated[1] >= END_THRESHOLD) 
            && (line_sensors_calibrated[2] >= END_THRESHOLD) 
            && (line_sensors_calibrated[3] >= END_THRESHOLD) 
            && (line_sensors_calibrated[4] >= END_THRESHOLD)) break;

            // get sensor values and determine left and right paths
            average_sensor_values();
            if (line_sensors_calibrated[0] >= SIDE_SENSOR_THRESHOLD) 
            if (line_sensors_calibrated[4] >= SIDE_SENSOR_THRESHOLD) 

            // check path derectly ahead
            average_sensor_values();
            if ((line_sensors_calibrated[1] >= MID_SENSORS_THRESHOLD) 
            || (line_sensors_calibrated[2] >= MID_SENSORS_THRESHOLD) 
            || (line_sensors_calibrated[3] >= MID_SENSORS_THRESHOLD))

            // check again if end point is reached
            refresh_sensor_values();
            if ((line_sensors_calibrated[0] >= END_THRESHOLD) 
            && (line_sensors_calibrated[1] >= END_THRESHOLD) 
            && (line_sensors_calibrated[2] >= END_THRESHOLD) 
            && (line_sensors_calibrated[3] >= END_THRESHOLD) 
            && (line_sensors_calibrated[4] >= END_THRESHOLD)) break;
            

            // turning according the recived
            sleep_ms(120);
            execute_turn(current_intersection);
            sleep_ms(100);
            is_intersection = 0;
            current_intersection++;

        }
    }

    // stop motors at end point
    motors_set_speeds(0, 0);
}
