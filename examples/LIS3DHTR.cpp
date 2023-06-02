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

#define LIS3DHTR_REG_ACCEL_WHO_AM_I (0x0F)      // Device identification Register
#define LIS3DHTR_REG_ACCEL_OUT_X_L (0x28)       // X-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_X_H (0x29)       // X-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_Y_L (0x2A)       // Y-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_Y_H (0x2B)       // Y-Axis Acceleration Data High Register
#define LIS3DHTR_REG_ACCEL_OUT_Z_L (0x2C)       // Z-Axis Acceleration Data Low Register
#define LIS3DHTR_REG_ACCEL_OUT_Z_H (0x2D)       // Z-Axis Acceleration Data High Register

I2c Wire;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    Wire.begin();
    printf("SystemClk:%ld\r\n",SystemCoreClock);


    if (Wire.readRegister(LIS3DHTR_REG_ACCEL_WHO_AM_I) != 51){
        printf("Failed to find sensor\n");
        while (1);
    }else{
        printf("Found LIS3DHTR\n");
    }

    while (1)
    {
        Delay_Ms(1000);
        uint8_t xAccelLo = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_X_L);
        uint8_t xAccelHi = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_X_H);
        int16_t x = (int16_t)((xAccelHi << 8) | xAccelLo);

        xAccelLo = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_Y_L);
        xAccelHi = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_Y_H);
                
        int16_t y = (int16_t)((xAccelHi << 8) | xAccelLo);

        xAccelLo = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_Z_L);
        xAccelHi = Wire.readRegister(LIS3DHTR_REG_ACCEL_OUT_Z_H);
                
        int16_t z = (int16_t)((xAccelHi << 8) | xAccelLo);

        printf("Lis3 X=%d, Y=%d Z=%d\r\n", x, y, z); 
    }

}