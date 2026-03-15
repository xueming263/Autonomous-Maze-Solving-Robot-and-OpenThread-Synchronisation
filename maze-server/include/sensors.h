#ifndef SENSORS_H
#define SENSORS_H
#include <stdint.h>

// initialization and bias calibration of sensors
void initialize_and_calibrate_sensors();

// refresh sensor values
void refresh_sensor_values();

// Calculate the average of ten sensor values 
// ​​and update the array. Time: 50ms
void average_sensor_values();

#endif // SENSORS_H
