/*
  custom_uart.c - Custom serial library
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
//#include <stdio.h>
//#include <stdlib.h>
#include "custom_uart.h"
#include "custom_uart_hw.h"
#include "common.h"

unsigned char* rxBuff;
unsigned long rxBuff_len;
unsigned long rxBuff_current;
unsigned long rxBuff_sizeOfData;

CustomUartHwConfiguration* hwConf;
CustomUartConfiguration* commConf;


void setRxBuffer(unsigned char* buff, unsigned long buff_len)
{
    rxBuff = buff;
    rxBuff_len = buff_len;
    rxBuff_current = 0;
    rxBuff_sizeOfData = 0;
}


void configureHardware(CustomUartHwConfiguration* conf)
{
    configurePin(conf->txPin, PIN_OUT);
    configurePin(conf->rxPin, PIN_IN);

    setRxBuffer(conf->rxBuffer, conf->rxBuffer_len);

    hwConf = conf;
}


void receiveChar()
{
    unsigned char newChar = readFromReceiveRegister();

    *(rxBuff + (rxBuff_sizeOfData + rxBuff_current) % rxBuff_len) = newChar;

    if (rxBuff_sizeOfData + 1 > rxBuff_len)
    {
        rxBuff_sizeOfData = rxBuff_len;
        rxBuff_current = (rxBuff_current + 1) % rxBuff_len;
    }
    rxBuff_sizeOfData = min(rxBuff_len, rxBuff_sizeOfData + 1);
}


int init(CustomUartConfiguration* conf)
{
    int ret = setUartParameters(
    conf->boudrate,
    conf->dataBits,
    conf->stopBits,
    conf->parity);

    if (ret != -1)
    {
        rxBuff_current = 0;
        rxBuff_sizeOfData = 0;
        commConf = conf;
    }

    configureInterrupt(hwConf->rxPin, DATA_RECEIVED, receiveChar);

    return ret;
}

void stop()
{
    unconfigureInterrupt(hwConf->rxPin, DATA_RECEIVED);
}

unsigned long read(unsigned char* buff, unsigned long maxData)
{
    unsigned long sizeOfData = min(maxData, rxBuff_sizeOfData);
    for (unsigned long i = 0; i < sizeOfData; i = i + 1)
    {
        *(buff+i) = *(rxBuff + (i + rxBuff_current) % rxBuff_len);
    }
    rxBuff_sizeOfData = rxBuff_sizeOfData - sizeOfData;
    rxBuff_current = (rxBuff_current + sizeOfData) % rxBuff_len;
    return sizeOfData;
}

void unconfigureOfWrite()
{
    stopSending(hwConf->txPin);
}

void write(unsigned char* buff, unsigned long buff_len)
{
    setBufferToSend(buff, buff_len);
    startSending(hwConf->txPin, unconfigureOfWrite);
}



