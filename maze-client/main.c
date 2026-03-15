#include "pico/stdlib.h"
#include <stdio.h>
#include "pololu_3pi_2040_robot.h"
#include "multi_display.h"
#include "follow_segment.h"
#include "maze_solve.h"
#include "path.h"
#include "sensors.h"
#include "turn.h"
#include "leds.h"
#include "uart_rx.h"

// globle varibles
char path[256];
unsigned int path_length = 0;
int is_intersection = 0;

int main()
{
    // initialization
    stdio_init_all();       // Initialize serial ports (for debugging and UART)
    motors_init();          // Initialize motors
    display_init();         // Initialize display
    rgb_leds_init();        // Initialize RGB LEDs

    // display the instrction of the project
    display_fill(0);
    multi_display("First press A then press the white button on Dongle to receive optimized path.", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(500);

    while (!button_a_is_pressed())
    {
        sleep_ms(10); // wait for button A to be pressed
    }
    
    // Initialize UART and start to receive data if fifo not empty
    setup_uart();
    sleep_ms(100);
    rev_data();

    display_fill(0);
    multi_display(path, 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(1000);

    initialize_and_calibrate_sensors(); // Initializing and calibrating the sensor

    // start maze solving and display
    display_fill(0);
    multi_display("Maze solving...", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(500); 

    maze_solve(); // Perform maze pathfinding (showing the path completed in the function in real time)

    run_led_sequence();

    display_fill(0);
    multi_display("Optimized path finished!", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(2000);

    multi_display("\n\n\nPlease reset or shutdown", 0, 0, COLOR_WHITE_ON_BLACK);

    // keep excuting
    while (1)
    {
        sleep_ms(100); // sleep
    }

    return 0;
}