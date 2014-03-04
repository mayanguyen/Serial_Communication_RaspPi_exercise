#ifndef UART_H
#define UART_H
 
#include <stdint.h>
 
/*
 * Initialize UART0.
 */
void uart_init();
 
/*
 * Transmit a byte via UART0.
 * uint8_t Byte: byte to send.
 */
void uart_putc(uint8_t byte);
 
/*
 * print a string to the UART one character at a time
 * const char *str: 0-terminated string
 */
void uart_puts(const char *str);

/*
 * returns a byte of data
 * 1 if no data is available
 */
int uart_getc();

/*
 * return a byte of data
 * blocks until there is data
 */
int uart_getcblock();
 
#endif // #ifndef UART_H
