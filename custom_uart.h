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

void configureHardware(CustomUartHwConfiguration* conf);

int init(CustomUartConfiguration* conf);

unsigned long read(unsigned char* buff, unsigned long maxData);

void write(unsigned char* buff, unsigned long buff_len);



#endif
