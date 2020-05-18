/*
  main.c - Custom serial library
  Copyright (c) 2020 Gyorgy Bacsi.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  This module provide example usage of uart library.*/
#include <stdio.h>
#include "common.h"
#include "custom_uart.h"
#include "custom_uart_hw.h"

#ifdef __cplusplus
extern "C"
#endif

extern unsigned char charToReceive;

int main(int argc, char *argv[])
{
    unsigned long sizeOfMyReadBuffer = 1024;
    unsigned char myReadBuffer[sizeOfMyReadBuffer];

    unsigned long sizeOfMyTempBuffer = 16;
    unsigned char myTempBuffer[sizeOfMyTempBuffer];
    unsigned long charRead;

    unsigned char myWriteBuffer[3] = {55,89,99};
    unsigned long sizeOfMyWriteBuffer = sizeof(myWriteBuffer);

    memset(myTempBuffer, 0, sizeOfMyTempBuffer);

    CustomUartConfiguration customConfig = {
        500, //boudrate
        8, //dataBits
        1, //stopBits
        None, //parity
    };

    CustomUartHwConfiguration customHwConfig = {
        0, //txPin
        1, //rxPin
        myReadBuffer, //rxBuffer
        sizeOfMyReadBuffer //rxBuffer_len
    };

    // Set up hardware
    configureHardware(&customHwConfig);

    // Set up communication parameters
    init(&customConfig);

    // Simulate some character incoming
    charToReceive = 33;
    receiveChar();
    charRead = read(myTempBuffer, sizeOfMyTempBuffer);
    printf("Character read: %lu (First character: %d)\n", charRead, (unsigned char) myTempBuffer[0]);

    // Sending a buffer on UART
    write(myWriteBuffer, sizeOfMyWriteBuffer);
}
