#include <Arduino.h>
#include "TMCDriver.h"
#include <stdint.h>

//DRVCTRL

void TMC2660::setMicroStep(uint8_t mStep) 
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

    constructBitField(bits, DRVCTRL_0); 
}

void TMC2660::constructBitField(uint32_t bits, uint32_t reg)
{
    DRVCTRL_0 = DRVCTRL_0 | bits; 
}

