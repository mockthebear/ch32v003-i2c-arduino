# ch32v003-i2c-arduino
An arduino-like library to use I2C somewhat compatible with arduino style of code

Not totally compatible, it still missing some features like the user_onRequest/user_onReceive whihc is not implemented.
push requests are welcome!

The usage is preety much like arduino...

```cpp
    Wire.beginTransmission(0x50);
    Wire.write(2);
    Wire.endTransmission(false);

    Wire.requestFrom(0x50, 9);

    printf("Read eeprom: ");

    while (Wire.available()){
        printf("%c", Wire.read());
    }

    printf("\r\n");
```
