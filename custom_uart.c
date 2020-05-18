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
#include "custom_uart.h"
#include "custom_uart_hw.h"
#include "common.h"

// Receive buffer related variables.
unsigned char* rxBuff;
unsigned long rxBuff_len;
unsigned long rxBuff_current;
unsigned long rxBuff_sizeOfData;

// Configuration storage
CustomUartHwConfiguration* hwConf;
CustomUartConfiguration* commConf;


// Set tx buffer tu further usage
void setRxBuffer(unsigned char* buff, unsigned long buff_len)
{
    rxBuff = buff;
    rxBuff_len = buff_len;
    rxBuff_current = 0;
    rxBuff_sizeOfData = 0;
}


/* Method: configureHardware

Configure hw related stuff.
:param CustomUartHwConfiguration* conf: Pointer to HW configuration
*/
void configureHardware(CustomUartHwConfiguration* conf)
{
    configurePin(conf->txPin, PIN_OUT);
    configurePin(conf->rxPin, PIN_IN);

    setRxBuffer(conf->rxBuffer, conf->rxBuffer_len);

    hwConf = conf;
}


/* Method: receiveChar

Callback function to interrupt of incoming data bytes.
*/
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


/* Method: Inint

Init our uart by setting boudrate, data and stop bits and parity.
  This method will return with -1 in case of some problem.
:param CustomUartConfiguration* conf: Pointer to the UART configuration.
:return int: Error flag
*/
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

/*Method: stop

Stopping method of uart receiving.
*/
void stop()
{
    unconfigureInterrupt(hwConf->rxPin, DATA_RECEIVED);
}

/* Method: read

Read data bytes to a buffer.
:param unsigned char* buff: Pointer to the output buffer
:param unsigned long maxData: Size of the output buffer
:return unsigned long: Return with the count of characters copied.
*/
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

/* Method: unconfigureOfWrite

Callback for the end of data writing.
*/
void unconfigureOfWrite()
{
    stopSending(hwConf->txPin);
}

/* Method: write

Send data on the UART.
:param unsigned char* buff: Buffer of the data to send
:param unsigned long buff_len: Length of the data to send.
*/
void write(unsigned char* buff, unsigned long buff_len)
{
    setBufferToSend(buff, buff_len);
    startSending(hwConf->txPin, unconfigureOfWrite);
}



