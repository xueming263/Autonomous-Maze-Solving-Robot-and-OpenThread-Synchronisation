#include "pico/stdlib.h"
#include <stdio.h>
#include "pololu_3pi_2040_robot.h"
#include "multi_display.h"
#include "follow_segment.h"
#include "maze_solve.h"
#include "path.h"
#include "sensors.h"
#include "turn.h"
#include "uart_tx.h"

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
    
    display_fill(0);
    multi_display("Press A to start solve maze.", 0, 0, COLOR_WHITE_ON_BLACK);

    while (!button_a_is_pressed())
    {
        sleep_ms(10); // wait for button A to be pressed
    }
    sleep_ms(500); 

    initialize_and_calibrate_sensors(); // Initializing and calibrating the sensor

    // start maze solving and display
    display_fill(0);
    multi_display("Maze solving...", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(1000); 
    
    // Perform maze pathfinding (showing the path completed in the function in real time)
    display_fill(0);
    maze_solve();

    // show maze completion information
    display_fill(0);
    multi_display("Maze solved!", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(1000);

    multi_display("\n\n\nPress A to display original path.", 0, 0, COLOR_WHITE_ON_BLACK);

    // wait for A press to display path
    while (!button_a_is_pressed())
    {
        sleep_ms(10);
    }

    display_fill(0);
    multi_display(path, 0, 0, COLOR_WHITE_ON_BLACK); // show the whole path
    sleep_ms(2000);

    multi_display("\n\n\nPress A to optimize path and display.", 0, 0, COLOR_WHITE_ON_BLACK);

    simplify_path(); // the path optimize function

    while (!button_a_is_pressed())
    {
        sleep_ms(10); 
    }
    
    // show optim path after A press
    display_fill(0);
    multi_display(path, 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(2000);

    multi_display("\n\n\nPress C to send Path with UART.", 0, 0, COLOR_WHITE_ON_BLACK);

    // wait for C pressed to start transmite data via UART
    while (!button_c_is_pressed())
    {
        sleep_ms(10);
    }

    // Initialize UART and start to transmite data via UART
    setup_uart();
    sleep_ms(100);
    send_data(path, path_length);
    sleep_ms(100);

    // show the path data is transmitted after all transmitted
    display_fill(0);
    multi_display("Optimized path transmitted!", 0, 0, COLOR_WHITE_ON_BLACK);
    sleep_ms(2000);

    multi_display("\n\n\nPlease reset or shutdown.", 0, 0, COLOR_WHITE_ON_BLACK);

    // keep excuting
    while (1)
    {
        sleep_ms(100); // sleep
    }

    return 0;
}