#include <pico/stdlib.h>
#include <stdio.h>
#include "display.h"
#include "ir_sensors.h"
#include "motors.h"
#include "multi_display.h"

void initialize_and_calibrate_sensors() {
    // initialize sensors
    line_sensors_start_read();
    sleep_ms(500);
    line_sensors_reset_calibration();

    display_fill(0);
    multi_display("Calibrating sensors...", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(1000);

    // calibration of sensors and motors at the maze entrance
    for(int i = 0; i < 2; i++)
    {
        motors_set_speeds(-600, -600);
        for (int j = 0; j < 20; j++) {
            line_sensors_calibrate();
            sleep_ms(10);
        }
        motors_set_speeds(0, 0);
        sleep_ms(100);

        motors_set_speeds(600, 600);
        for (int j = 0; j < 25; j++) {
            line_sensors_calibrate();
            sleep_ms(10);
        }
        motors_set_speeds(0, 0);
        sleep_ms(100);
    }

    multi_display("\nSensors calibration done.", 0, 0, COLOR_WHITE_ON_BLACK);
    display_show();
    sleep_ms(1000);
}

// update sensor values
void refresh_sensor_values() {
    line_sensors_read_calibrated(); // get new sensor values
}

// calculate the average sensor values to smoothy the line keeping control Time:50ms
void average_sensor_values() {
    int sum[5] = {0}; // accumulate value of each sensor

    for (int i = 0; i < 10; i++) { // total 10 times in 50 ms
        refresh_sensor_values();
        sleep_ms(5);
        for (int j = 0; j < 5; j++) {
            sum[j] += line_sensors_calibrated[j];
        }
    }

    for (int k = 0; k < 5; k++) {
        line_sensors_calibrated[k] = sum[k] / 10; // calculate average values
    }
}
