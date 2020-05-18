#define TESTING_PACKAGE

#include <stdio.h>
#include "custom_uart.h"
#include "custom_uart_hw.h"

#ifdef __cplusplus
extern "C"
#endif
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

    printf("asd\n");

    // Simulate some character incoming
    charToReceive = 12;
    printf("asd2\n");
    receiveChar();
    printf("asd3\n");
    charRead = read(myTempBuffer, sizeOfMyTempBuffer);
    printf("asd4\n");
    printf("Character readed: %d\n", charRead);
    printf("asd5\n");


}
