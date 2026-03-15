#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "display.h"
#include "rgb_leds.h"

#define UART_ID uart0
#define PICO_DEFAULT_UART_BAUD_RATE 115200
#define UART_TX_PIN 28 // TX Pin
//#define UART_RX_PIN 29 // RX Pin(not use by tx)

static rgb_color color_led[3] = {
    {255,0,0},
    {0,255,0},
    {0,0,255}
};
static uint8_t brightness = 15;
static uint32_t count = 3;

void setup_uart() {
    // Initialize UART
    uart_init(UART_ID, PICO_DEFAULT_UART_BAUD_RATE);
    
    // Set UART TX and RX pins
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    //gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART format (8-bit data, no parity, 1 stop bit)
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

    if(!uart_is_enabled(UART_ID)){
        display_fill(0);
        display_text("uart failed enabled", 0, 0, COLOR_BLACK_ON_WHITE);
        display_show();
    }

    // Enable UART FIFO
    uart_set_fifo_enabled(UART_ID, true);
}

// Send data via UART
void send_data(char *buf, unsigned int len) {
    
    rgb_leds_init(); // initialize rgb leds

    for (unsigned int i = 0; i < len; i++){
        char path_char = buf[i];
        uart_putc(UART_ID, path_char);
    }
    uart_putc(UART_ID, '\0'); // put string in fifo one by one

    // leds flash after successfully tranmission
    rgb_leds_write(color_led, count, brightness);
    sleep_ms(200);
    rgb_leds_off();

}


