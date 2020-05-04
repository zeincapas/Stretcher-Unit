#ifndef BITFIELDS_H_
#define BITFIELDS_H_

struct DRVCONF
{
    const uint32_t address = 0x07;

};

struct DRVCTRL_0       //STEP and DIR mode
{
    const uint32_t address = 0b00;
    const uint32_t mstep = 0b1111;
    const uint32_t intpol = 0b1 << 9;
    const uint32_t dedge = 0b1 << 8;
};

struct DRVCTRL_1       //SPI mode
{
    const uint32_t address = 0x00;

};

struct CHOPCONF
{
    const uint32_t address = 0x04;

};

struct SMARTEN
{
    const uint32_t address = 0x05;

};

struct SGCSCONF
{
    const uint32_t address = 0x06;

};


#endif
