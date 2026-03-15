#include "display.h"
#include "multi_display.h"
#include <stdio.h>
#include <stdint.h>
#include "ir_sensors.h"

#define FONT_WIDTH 8        // font width
#define FONT_HEIGHT 8       // font height
#define LINE_SPACING 2      // line spacing

#define SENSOR_COUNT 5       // number of sensors
#define MAX_SENSOR_VALUE 1023 // sensor max value (10 bits ADC)
#define BAR_WIDTH 20          // width of each bar
#define BAR_SPACING 7         // spacing between each bar
#define BAR_HEIGHT 48         // max. bar height (pixel)

#define SCREEN_WIDTH 128      // display width
#define SCREEN_HEIGHT 64      // dsplay height


// show path on display
void multi_display(const char *text, int x, int y, uint8_t flags)
{
     // Iterating over string
    while (*text)
    {
        // If the edge of the screen is reached or a newline character 
        // '\n' is encountered, it will go to the next line.
        if (*text == '\n' || x + FONT_WIDTH > SCREEN_WIDTH)
        {
            x = 0;                       // back to the first line on display
            y += FONT_HEIGHT + LINE_SPACING; // to next line
            if (y + FONT_HEIGHT > SCREEN_HEIGHT) // exceede display height
            {
                break; // stop avoid exceeding
            }

            if (*text == '\n') // skip when '\n'
            {
                text++;
                continue;
            }
        }

        // show one string
        display_text(text, x, y, flags);
        x += FONT_WIDTH; // move to next string
        text++;
    }

    // refresh display
    display_show();
}

void display_sensor_bars()
{   
    int x = 0; // starting x corrdinate

    // get each sensor's value and show bar graph
    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        // Get the current sensor value and scale it to the screen height
        uint16_t sensor_value = line_sensors_calibrated[i];
        int bar_height = (sensor_value * BAR_HEIGHT) / MAX_SENSOR_VALUE;

        // display a bar chat (from bottom up)
        display_fill_rect(x, SCREEN_HEIGHT - bar_height, BAR_WIDTH, bar_height, COLOR_WHITE_ON_BLACK);

        // update starting x coordinate with spacing
        x += BAR_WIDTH + BAR_SPACING;
    }

    // refresh display
    display_show();
}