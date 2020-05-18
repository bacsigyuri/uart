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

// Transmit related functions

/* Method: startSending

Start sending from data buffer.
:param unsigned char pinNumber: Pin number of TX.
:param void (*f)(): callback for the end of sending from the buffer.
*/
void startSending(unsigned char pinNumber, void (*f)());

/* Method: setBufferToSend

Set buffer for sending data. Buffer received here will be used to send data to UART.
  Sending is parallel by running main code. Be sure, this buffer do not change form outside during sending process.
:param unsigned char* buff: Buffer of data
:param unsigned long buffLen: Length of the data
*/
int setBufferToSend(unsigned char* buff, unsigned long buffLen);

/* Method: stopSending

Clean UART sending setting.
:param unsigned char pinNumber: pin number
*/
void stopSending(unsigned char pinNumber);

/*Method: readFromReceiveRegister

Read one-byte data from the HW buffer
:return unsigned char: Return with data received
*/
unsigned char readFromReceiveRegister();

#endif
