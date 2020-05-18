/*
  custom_uart.h - Custom serial library
  Copyright (c) 2020 Gyorgy Bacsi.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#ifndef custom_uart_h
#define custom_uart_h

#include "custom_uart_hw.h"

typedef struct {
    unsigned long boudrate;
    unsigned char dataBits;
    unsigned char stopBits;
    Parity parity;
} CustomUartConfiguration;

typedef struct {
    unsigned char txPin;
    unsigned char rxPin;
    unsigned char* rxBuffer;
    unsigned long rxBuffer_len;
} CustomUartHwConfiguration;

/* Method: configureHardware

Configure hw related stuff.
:param CustomUartHwConfiguration* conf: Pointer to HW configuration
*/
void configureHardware(CustomUartHwConfiguration* conf);

/* Method: Inint

Init our uart by setting boudrate, data and stop bits and parity.
  This method will return with -1 in case of some problem.
:param CustomUartConfiguration* conf: Pointer to the UART configuration.
:return int: Error flag
*/
int init(CustomUartConfiguration* conf);

/* Method: stop

Stopping method of uart receiving.
*/
void stop();

/* Method: read

Read data bytes to a buffer.
:param unsigned char* buff: Pointer to the output buffer
:param unsigned long maxData: Size of the output buffer
:return unsigned long: Return with the count of characters copied.
*/
unsigned long read(unsigned char* buff, unsigned long maxData);

/* Method: write

Send data on the UART.
:param unsigned char* buff: Buffer of the data to send
:param unsigned long buff_len: Length of the data to send.
*/
void write(unsigned char* buff, unsigned long buff_len);



#endif
