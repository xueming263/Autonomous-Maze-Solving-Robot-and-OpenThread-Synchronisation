#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "display.h"
#include "multi_display.h"
#include "path.h"
#include "rgb_leds.h"

#define UART_ID uart0
#define PICO_DEFAULT_UART_BAUD_RATE 115200
#define UART_RX_PIN 29
#define MAX_BUFFER_SIZE 256

rgb_color color_debug[] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
}; // set rgb colors

void setup_uart(){
    uart_init(UART_ID, PICO_DEFAULT_UART_BAUD_RATE);
    
    // Set UART TX and RX pins
    //gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART format (8-bit data, no parity, 1 stop bit)
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

    if(!uart_is_enabled(UART_ID)){
        display_fill(0);
        multi_display("UART0 failed to enable", 0, 0, COLOR_WHITE_ON_BLACK);
    }

    // Enable UART FIFO
    uart_set_fifo_enabled(UART_ID, true);
}

void rev_data(){

    int buffer_index = 0; 

    while(1){
        
        if (uart_is_readable(UART_ID)) {  // start transmitting when fifo not empty
            char rev_command = uart_getc(UART_ID); // get one string
            rgb_leds_write(color_debug, 3, 15); // turn on leds after successfully receive
            sleep_ms(20);
            rgb_leds_off();

            if (buffer_index < MAX_BUFFER_SIZE - 1) {// show if overflow on display
                path[buffer_index++] = rev_command;
            }
            else {
                display_fill(0);
                multi_display("Buffer overflow", 0, 0, COLOR_WHITE_ON_BLACK);
                sleep_ms(2000);
                return;
            }

            if (!uart_is_readable(UART_ID)) { // stop UART after fifo empty detected
                break;
            } 
        }
    }
}
