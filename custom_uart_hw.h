/*
  custom_uart_hw.h - Custom serial library
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

#ifndef custom_uart_hw_h
#define custom_uart_hw_h

typedef enum {None=0, Odd=1, Even=2} Parity;
typedef enum {PIN_OUT=0, PIN_IN=1} pinType;
typedef enum {DATA_SENT=0, DATA_RECEIVED=1} interruptType;

void configurePin(unsigned char pinNumber, pinType pt);

int setUartParameters(
    unsigned long boudrate,
    unsigned char dataBits,
    unsigned char stopBits,
    Parity parity);

void startSending(unsigned char pinNumber, void (*f)());

int setBufferToSend(unsigned char* buff, unsigned long buffLen);

void stopSending(unsigned char pinNumber);

unsigned char readFromReceiveRegister();

#ifdef TESTING_PACKAGE
unsigned char charToReceive;
#endif // TESTING_PACKAGE

#endif
