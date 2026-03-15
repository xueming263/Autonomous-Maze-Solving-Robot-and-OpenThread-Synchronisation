#include <stdint.h>
#include "pico/stdlib.h"
#include "sensors.h"
#include "ir_sensors.h"
#include "motors.h"
#include "follow_segment.h"
#include "multi_display.h"
#include "display.h"

int read_position()
{
    unsigned char on_line = 0;
    unsigned long avg = 0;  // Weighted total value (long integer, to avoid overflow)
    unsigned int sum = 0;   // sum, used to calculate the denominator
    static int last_position = 0;

    // Traverse all sensor values and calculate the weighted average
    for (unsigned char i = 0; i < 4; i++)
    {
        unsigned int value = line_sensors_calibrated[i];

        // Determine whether the line is detected
        if (value > 100)  // Threshold of sensors value when detecting lines
        {
            on_line = 1;
        }
        if (value > 30)
        {
            avg += (unsigned long)value * (i * 1000);   //weighted calculation
            sum += value;                               //accumulate sensor values
        }
    }

    // if deviation from line center is detected
    if (!on_line)
    {
        // if the previous position was on the left of line, return 0
        if (last_position < 2000)
        {
            return 0;
        }
        // If the previous position was on the right, return the maximum value
        else
        {
            return 4000;
        }
    }

    // Calculate and return the current line position, the base value is 2000
    last_position = avg / sum;
    return last_position;
}

void follow_segment()
{
    int last_proportional = 0;
    const int Kp = 0.8 * 100;   // proportional factor
    const int Kd = 2.2 * 100;    // differential factor

    while (is_intersection == 0)
    {
        // get and display sensor values
        refresh_sensor_values();

        // 显示路径和传感器柱状图
        display_fill(0);
        multi_display(path, 0, 0, COLOR_WHITE_ON_BLACK);
        display_sensor_bars();

        unsigned int position = read_position();

        // calculate PD control variables
        int proportional = ((int)position) - 2000;
        int derivative = proportional - last_proportional;

        // record the last deviation
        last_proportional = proportional;

        // calculate motor speed difference
        int power_difference = (Kp * proportional / 100) + (Kd * derivative / 100);

        // limit maximum speed
        const int max_speed = 600;
        if (power_difference > max_speed)
            power_difference = max_speed;
        if (power_difference < -max_speed)
            power_difference = -max_speed;

        // Adjust the left and right motors according to the speed difference
        if (power_difference < 0)
            motors_set_speeds(max_speed + power_difference, max_speed);
        else
            motors_set_speeds(max_speed, max_speed - power_difference);
        
        // determin if is forwarding intersection
        if((line_sensors_calibrated[1] <= 300) 
        && (line_sensors_calibrated[2] <= 300) 
        && (line_sensors_calibrated[3] <= 300)) // there is no line ahead
		{   
            motors_set_speeds(500, 500); // Slow down and continue forward until you reach the turn.
            sleep_ms(50);
            is_intersection = 1;
			return;
		}
        // line detected on ether side of car
		else if((line_sensors_calibrated[0] >= 500) || (line_sensors_calibrated[4] >= 500))
		{
            motors_set_speeds(500, 500);
            sleep_ms(50);
            is_intersection = 1;
			return;
		}
    }
}
