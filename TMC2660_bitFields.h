#ifndef TMC2660_BITFIELDS_H_
#define TMC2660_BITFIELDS_H_

#include <stdint.h>

struct DRIVERCONF
{
    const uint8_t address = 0b111;
    
};

struct DRVCTRL_0       //STEP and DIR mode
{
    const uint8_t address = 0b00;
};

struct DRVCTRL_1       //SPI mode
{
    const uint8_t address = 0b00;

};

struct CHOPCONF
{
    const uint8_t address = 0b100;

};

struct SMARTEN
{
    const uint8_t address = 0b101;

};

struct SGCSCONF
{
    const uint8_t address = 0b110;

};


#endif
