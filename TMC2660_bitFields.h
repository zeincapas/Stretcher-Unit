#ifndef TMC2660_BITFIELDS_H_
#define TMC2660_BITFIELDS_H_

#include <stdint.h>

struct DRVCONF
{
    const uint8_t address = 0x07;

};

struct DRVCTRL_0       //STEP and DIR mode
{
    const uint8_t address = 0x00;
};

struct DRVCTRL_1       //SPI mode
{
    const uint8_t address = 0x00;

};

struct CHOPCONF
{
    const uint8_t address = 0x04;

};

struct SMARTEN
{
    const uint8_t address = 0x05;

};

struct SGCSCONF
{
    const uint8_t address = 0x06;

};


#endif
