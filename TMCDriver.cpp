#include "TMCDriver.h"
#include "bitFields.h"
#include <SPI.h>

DRVCTRL_0 DRVCTRL;

/****************************************
***********       INIT       ************
****************************************/
void TMC2660::init()
{
    pinMode(cs, OUTPUT);
    pinMode(en, OUTPUT);
    digitalWrite(en, LOW);      // Enable driver in hardware
}


/****************************************
*********** DRVCTRL FUNCTIONS ***********
****************************************/
void TMC2660::setMicroStep(uint16_t mStep) 
{   
    uint32_t bits;
    switch(mStep)
    {
        case 256:   bits = 0x00; break;
        case 128:   bits = 0x01; break;
        case  64:   bits = 0x02; break;
        case  32:   bits = 0x03; break;
        case  16:   bits = 0x04; break;
        case   8:   bits = 0x05; break;
        case   4:   bits = 0x06; break;
        case   2:   bits = 0x07; break;
        case   1:   bits = 0x08; break;    
    }

    modifyBits(DRVCTRL.mstep, bits, &DRVCTRL_0_CMD); 
}

void TMC2660::doubleStepping(bool flag)
{
    uint32_t bits;
    uint8_t shift = 8;

    if (flag)
    {
        bits = 1 << shift;
    }
    else
    {
        bits = 0 << shift;
    }
    modifyBits(DRVCTRL.dedge, bits, &DRVCTRL_0_CMD);
}

void TMC2660::stepInterpolation(bool flag)
{
    uint32_t bits;
    uint8_t shift = 9;

    if (flag)
    {
        bits = 1 << shift; 
    }
    else 
    {
        bits = 0 << shift;
    }
    modifyBits(DRVCTRL.intpol, bits, &DRVCTRL_0_CMD);
}

void TMC2660::modifyBits(uint32_t mask, uint32_t edit, uint32_t* reg)
{
    //clear the register first and then "OR" it after. 
    *reg = (*reg & ~mask) | edit;
}

