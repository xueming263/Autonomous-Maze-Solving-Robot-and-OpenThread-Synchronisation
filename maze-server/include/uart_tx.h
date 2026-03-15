#ifndef UART_TX_H
#define UART_TX_H

void setup_uart(); // initialization of UART

void send_data(const char *buf, int len); // transmission of path to dongle

#endif 