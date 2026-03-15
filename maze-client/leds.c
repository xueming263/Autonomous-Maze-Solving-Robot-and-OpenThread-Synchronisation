#include "pico/stdlib.h"
#include "pololu_3pi_2040_robot.h"

rgb_color colors[] = {
    {255, 0, 0},    // red
    {0, 255, 0},    // green
    {0, 0, 255},    // blue
    {255, 255, 0},  // yellow
    {0, 255, 255},  // cyan
    {255, 0, 255},  // purple
    {255, 255, 255} // white
};


// define buzzer sequence
//const char *song = ">c32>d32>e32>f32>g16<p16>a16<b16>c32";


// Display the revolving lantern effect
void run_led_sequence() {
    int num_leds = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < num_leds; i++) {
        rgb_leds_write(colors, 7, 15); // set the leds and their colors
        sleep_ms(20); // keep lightning for 20ms
        rgb_leds_off(); // turn off LED
        sleep_ms(100); // flashing interval 100ms
    }
}