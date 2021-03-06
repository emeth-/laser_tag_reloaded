/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/


#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

/* Conditional extern "C" so we're safe to call from C++ files */
#ifdef __cplusplus
extern "C" {
#endif

#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <libmaple/usart.h>

#define BLUETOOTH_BAUD 115200
#define BLUETOOTH_USART USART2
#define BLUETOOTH_PORT_TX GPIOA
#define BLUETOOTH_PORT_RX GPIOA
#define BLUETOOTH_PIN_TX 2
#define BLUETOOTH_PIN_RX 3
#define BLUETOOTH_AFIO_EXTI_PIN AFIO_EXTI_3
#define BLUETOOTH_AFIO_EXTI_PORT AFIO_EXTI_PA 


void bluetooth_start(void);
void bluetooth_end(void);
uint32 bluetooth_available(void);
uint8 bluetooth_read(void);
void bluetooth_writeChar(unsigned char);
void bluetooth_writeString(const char *str);
void bluetooth_writeUnsignedInt(uint32);
void bluetooth_println(void);
void bluetooth_printString(const char[]);
void bluetooth_printlnString(const char[]);
void bluetooth_printChar(char);
void bluetooth_printlnChar(char);
void bluetooth_flush(void);

#ifdef __cplusplus
}
#endif

#endif 