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

#include "custom_uart_hw.h"
#include <stddef.h>

unsigned char* txBuff = NULL;
unsigned long txBuffLen;
unsigned long txBuffPointer;
void (*callbackAtEndOfSending)();


void configurePin(unsigned char pinNumber, pinType pt)
{
    #ifdef TESTING_PACKAGE
        print("Pin configured: pinNumber: %d, pinType: %d\n", pinNumber, pt);
    #endif // TESTING_PACKAGE
    // TODO
}

void configureInterrupt(unsigned char pinNumber, interruptType it, void (*interruptHandler)())
{
    #ifdef TESTING_PACKAGE
        print("configureInterrupt: pinNumber: %d, interruptType: %d\n", pinNumber, it);
    #endif // TESTING_PACKAGE
    // TODO
}

void unconfigureInterrupt(unsigned char pinNumber, interruptType it)
{
    #ifdef TESTING_PACKAGE
        print("unconfigureInterrupt: pinNumber: %d, interruptType: %d\n", pinNumber, it);
    #endif // TESTING_PACKAGE
    // TODO
}

void placeDataToHWSendBuffer(unsigned char data)
{
    #ifdef TESTING_PACKAGE
        print("placeDataToHWSendBuffer: pinNumber: %d\n", data);
    #endif // TESTING_PACKAGE
    //TODO
}

void callSendingMethod()
{
    #ifdef TESTING_PACKAGE
        print("callSendingMethod called\n");
    #endif // TESTING_PACKAGE
    //TODO
}

unsigned char readFromReceiveRegister()
{
    #ifdef TESTING_PACKAGE
        print("readFromReceiveRegister called, returned %d\n", charToReceive);
        return charToReceive;
    #endif // TESTING_PACKAGE
    //TODO
}

int setUartParameters(
    unsigned long boudrate,
    unsigned char dataBits,
    unsigned char stopBits,
    Parity parity)
{
    #ifdef TESTING_PACKAGE
        print("setUartParameters: boudrate: %d, dataBits: %d, stopBits: %d, parity: %d\n", boudrate, dataBits, stopBits, parity);
        return 0;
    #endif // TESTING_PACKAGE

    // TODO
}

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

void sendChar()
{
    if (txBuff != NULL && txBuffLen > txBuffPointer )
    {
        placeDataToHWSendBuffer(*(txBuff+txBuffPointer));
        txBuffPointer++;
        callSendingMethod();
    } else callbackAtEndOfSending();
}

void startSending(unsigned char pinNumber, void (*f)())
{
    configureInterrupt(pinNumber, DATA_SENT, sendChar);
    callbackAtEndOfSending = f;
    sendChar();
}

void stopSending(unsigned char pinNumber)
{
    unconfigureInterrupt(pinNumber, DATA_SENT);
}

