#pragma once

/*
Version made by Matheus Braga Almeida
*/

#include <stdint.h>
#include <stddef.h>

#define BUFFER_LENGTH 20


class I2c{
    public:
        I2c();

        void begin();
        void begin(uint8_t);
        void begin(int);

        void end();
        void setClock(uint32_t);

        void setWireTimeout(uint32_t timeout = 25000, bool reset_with_timeout = false);
        bool getWireTimeoutFlag(void);
        void clearWireTimeoutFlag(void);
        
        void beginTransmission(uint8_t);
        void beginTransmission(int);
        uint8_t endTransmission(void);
        uint8_t endTransmission(uint8_t);

        uint8_t requestFrom(uint8_t, uint8_t);
        uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
        uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
        uint8_t requestFrom(int, int);
        uint8_t requestFrom(int, int, int);



        uint8_t readRegisters(uint8_t address, uint8_t* data, size_t length);
        int readRegister(uint8_t address);
        int writeRegister(uint8_t address, uint8_t value);

        virtual size_t write(uint8_t);
        virtual size_t write(const uint8_t *, size_t);

        virtual int available(void);
        virtual int read(void);
        virtual int peek(void);
        virtual void flush(void);

    private:
        static uint8_t rxBufferIndex;
        static uint8_t rxBufferLength;
        static uint8_t txAddress;
        static uint32_t txClock;
        static uint8_t txBufferIndex;
        static uint8_t txBufferLength;
        static uint8_t transmitting;
        static void SetupI2C(bool force);
        static void ApplyI2CConfig();
        static bool started;

        static uint8_t txBuffer[BUFFER_LENGTH];
        static uint8_t rxBuffer[BUFFER_LENGTH];

        static uint8_t twi_writeTo(uint8_t txAddress, uint8_t *txBuffer, uint16_t txBufferLength, bool sendStop);
        static uint8_t twi_readFrom(uint8_t txAddress, uint8_t *txBuffer, uint16_t txBufferLength, bool sendStop);
        static bool twi_transmit(const uint8_t *bytes, size_t count);
};