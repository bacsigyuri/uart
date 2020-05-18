/*
  custom_uart_hw.c - Custom serial library
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

#include "common.h"
#include "custom_uart_hw.h"
#include <stddef.h>

#ifdef TESTING_PACKAGE
// This variable represent the character received and stored on the UART buffer of the MC.
unsigned char charToReceive;
#endif // TESTING_PACKAGE

// Transmitter buffer related variables and callbacks.
unsigned char* txBuff = NULL;
unsigned long txBuffLen;
unsigned long txBuffPointer;
void (*callbackAtEndOfSending)();


/* Method: configurePin

Configure digital pin to send or receive data. This function should convert pin number to hw address.
:param unsigned char pinNumber: Number of the pin
:param pinType pt: Type of the pin
*/
void configurePin(unsigned char pinNumber, pinType pt)
{
    #ifdef TESTING_PACKAGE
        printf("Pin configured: pinNumber: %d, pinType: %d\n", pinNumber, pt);
    #endif // TESTING_PACKAGE
    // TODO
}

/* Method: configureInterrupt

Configure interrupt to handle asynchronous communication.
:param unsigned char pinNumber: Number of the pin
:param interruptType it: Interrupt type
:param void (*interruptHandler)(): Callback for interrupt set.
*/
void configureInterrupt(unsigned char pinNumber, interruptType it, void (*interruptHandler)())
{
    #ifdef TESTING_PACKAGE
        printf("configureInterrupt: pinNumber: %d, interruptType: %d\n", pinNumber, it);
    #endif // TESTING_PACKAGE
    // TODO
}

/* Method: unconfigureInterrupt

Remove interrupt.
:param unsigned char pinNumber: Number of the pin
:param interruptType it: Interrupt type
*/
void unconfigureInterrupt(unsigned char pinNumber, interruptType it)
{
    #ifdef TESTING_PACKAGE
        printf("unconfigureInterrupt: pinNumber: %d, interruptType: %d\n", pinNumber, it);
    #endif // TESTING_PACKAGE
    // TODO
}

/* Method: placeDataToHWSendBuffer

Place one-byte data to the data buffer of the HW.
:param unsigned char data: Byte to the buffer.
*/
void placeDataToHWSendBuffer(unsigned char data)
{
    #ifdef TESTING_PACKAGE
        printf("placeDataToHWSendBuffer: data: %d\n", data);
    #endif // TESTING_PACKAGE
    //TODO
}

/* Method: callSendingMethod

Start sending data from the data buffer.
*/
void callSendingMethod()
{
    #ifdef TESTING_PACKAGE
        printf("callSendingMethod called\n");
        sendChar();
    #endif // TESTING_PACKAGE
    //TODO
}

/*Method: readFromReceiveRegister

Read one-byte data from the HW buffer
:return unsigned char: Return with data received
*/
unsigned char readFromReceiveRegister()
{
    #ifdef TESTING_PACKAGE
        printf("readFromReceiveRegister called, returned %d\n", charToReceive);
        return charToReceive;
    #endif // TESTING_PACKAGE
    //TODO
}

/* Method: setUartParameters

Set UART parameter for the communication.
:param unsigned long boudrate: Boudrate of the UART communication
:param unsigned char dataBits: Data bits
:param unsigned char stopBits: Stop bit
:param Parity parity: Parity setting
*/
int setUartParameters(
    unsigned long boudrate,
    unsigned char dataBits,
    unsigned char stopBits,
    Parity parity)
{
    #ifdef TESTING_PACKAGE
        printf("setUartParameters: boudrate: %d, dataBits: %d, stopBits: %d, parity: %d\n", boudrate, dataBits, stopBits, parity);
        return 0;
    #endif // TESTING_PACKAGE

    // TODO
}

/* Method: setBufferToSend

Set buffer for sending data. Buffer received here will be used to send data to UART.
  Sending is parallel by running main code. Be sure, this buffer do not change form outside during sending process.
:param unsigned char* buff: Buffer of data
:param unsigned long buffLen: Length of the data
*/
int setBufferToSend(unsigned char* buff, unsigned long buffLen)
{
    if (txBuff == NULL)
    {
        txBuff = buff;
        txBuffLen = buffLen;
        txBuffPointer = 0;
    }

    if (buffLen == 0) txBuff = NULL;

    if (txBuff == NULL) return -1; else return 0;
}

/* Method: sendChar

Send a character on UART from buffer.
*/
void sendChar()
{
    if (txBuff != NULL && txBuffLen > txBuffPointer )
    {
        placeDataToHWSendBuffer(*(txBuff+txBuffPointer));
        txBuffPointer++;
        callSendingMethod();
    } else callbackAtEndOfSending();
}

/* Method: startSending

Start sending from data buffer.
:param unsigned char pinNumber: Pin number of TX.
:param void (*f)(): callback for the end of sending from the buffer.
*/
void startSending(unsigned char pinNumber, void (*f)())
{
    // Connect sendChar method to interrupt, which is triggered at the end of sending data from HW buffer.
    configureInterrupt(pinNumber, DATA_SENT, sendChar);

    // Store callback to module variable
    callbackAtEndOfSending = f;

    // Send the first character.
    sendChar();
}

/* Method: stopSending

Clean UART sending setting.
:param unsigned char pinNumber: pin number
*/
void stopSending(unsigned char pinNumber)
{
    unconfigureInterrupt(pinNumber, DATA_SENT);
}

