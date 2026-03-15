#ifndef FOLLOW_SEGMENT_H
#define FOLLOW_SEGMENT_H

/**
 * Keep the robot moving along the line segment
 * 
 * This function uses the sensor data to adjust 
 * the motor speeds so that the robot stays on the 
 * line segment.
 */

int read_position();

void follow_segment();

extern int is_intersection;

#endif // FOLLOW_SEGMENT_H