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
    const uint32_t dedge = 0b1 << 8;
    const uint32_t intpol = 0b1 << 9;
};

struct DRVCTRL_1       //SPI mode
{
    const uint32_t address = 0x00;

};

struct CHOPCONF
{
    const uint32_t address = 0b100;
    const uint32_t toff = 0b1111;
    const uint32_t hstrt = 0b111 << 4;
    const uint32_t hend = 0b1111 << 7;
    const uint32_t hdec = 0b11 << 11;
    const uint32_t rndtf = 0b1 << 13;
    const uint32_t chm = 0b1 << 14;
    const uint32_t tbl = 0b11 << 15;
};

struct SMARTEN
{
    const uint32_t address = 0b101;

};

struct SGCSCONF
{
    const uint32_t address = 0x06;

};


#endif
