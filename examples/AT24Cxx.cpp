#if defined(CH32V00X)
#include <ch32v00x.h>
#elif defined(CH32V10X)
#include <ch32v10x.h>
#elif defined(CH32V20X)
#include <ch32v20x.h>
#elif defined(CH32V30X)
#include <ch32v30x.h>
#endif


/*
Version made by Matheus Braga Almeida
*/

#include <debug.h>

#include "i2c.hpp"


I2c Wire;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    Wire.begin();
    printf("SystemClk:%ld\r\n",SystemCoreClock);

    char hello[] = "CH32V003!";

    Wire.beginTransmission(0x50);
    Wire.write(2);
    Wire.write((uint8_t*)hello, sizeof(hello));

    if (Wire.endTransmission(true) == 0){
        printf("Success written!\r\n");
    }   

    Wire.beginTransmission(0x50);
    Wire.write(2);
    Wire.endTransmission(false);

    Wire.requestFrom(0x50, 9);

    printf("Read eeprom: ");

    while (Wire.available()){
        printf("%c", Wire.read());
    }

    printf("\r\n");
    

    while (1);

}