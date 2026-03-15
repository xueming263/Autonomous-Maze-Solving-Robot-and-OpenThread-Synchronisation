#ifndef MULTI_DISPLAY_H
#define MULTI_DISPLAY_H

// global path array and length
extern char path[256];
extern unsigned int path_length;

// path display function
void multi_display(const char *text, int x, int y, uint8_t flags);

// sensor value display via bar graph
void display_sensor_bars();

#endif // MULTI_DISPLAY_H