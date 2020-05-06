#include "TMCDriver.h"
#include "bitFields.h"
#include <SPI.h>

DRVCTRL_0 drvctrl;
CHOPCONF chopconf;
DRVCONF drvconf;
SMARTEN smarten;
SGCSCONF sgcsconf;

/*********************************************************************************
************************************ INIT/SPI FUNCTIONS **************************
*********************************************************************************/
void TMC2660::init()
{
    pinMode(cs, OUTPUT);
    pinMode(en, OUTPUT);
    digitalWrite(en, LOW);      // Enable driver in hardware
}

void TMC2660::modifyBits(uint32_t mask, uint32_t edit, uint32_t* reg)
{
    //clear the register first and then "OR" it after. 
    *reg = (*reg & ~mask) | edit;
}


void TMC2660::write(uint32_t* cmd)
{
    //Acquire constructed bitfield and chop it up to 4 bytes. 
    char writeField[4] = {*cmd >> 24, (*cmd >> 16) & 0xFF, (*cmd >> 8) & 0xFF, (*cmd) & 0xFF};
    SPI.begin();
    digitalWrite(cs, LOW);
    SPI.transfer(&writeField, 4);
    digitalWrite(cs, HIGH);
    SPI.endTransaction();
}


/*********************************************************************************
************************************ DRVCTRL FUNCTIONS ***************************
*********************************************************************************/

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
    modifyBits(drvctrl.mstep, bits, &DRVCTRL_0_CMD);
    // write(&DRVCTRL_0_CMD); 
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
    modifyBits(drvctrl.dedge, bits, &DRVCTRL_0_CMD);
    // write(&DRVCTRL_0_CMD); 
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
    modifyBits(drvctrl.intpol, bits, &DRVCTRL_0_CMD);
    // write(&DRVCTRL_0_CMD); 
}

/*********************************************************************************
************************************ CHOPCONF FUNCTIONS **************************
*********************************************************************************/

void TMC2660::slowDecayTime(uint8_t offTime)
{
    uint32_t bits;
    if (offTime > 15)
    {
        bits = 15;
    }
    else
    {
        bits = offTime;
    }
    modifyBits(chopconf.toff, bits, &CHOPCONF_CMD);
}

void TMC2660::hystStart(uint8_t sOffset)
{
    uint32_t bits;
    uint8_t shift = 4;
    switch(sOffset)
    {
        case   8:   bits = 0x07; break;
        case   7:   bits = 0x06; break;
        case   6:   bits = 0x05; break;
        case   5:   bits = 0x04; break;
        case   4:   bits = 0x03; break;
        case   3:   bits = 0x02; break;
        case   2:   bits = 0x01; break;
        case   1:   bits = 0x00; break;    
    }
    bits = bits << shift;
    modifyBits(chopconf.hstrt, bits, &CHOPCONF_CMD);
}

void TMC2660::hystEnd(int8_t eOffset)
{
    uint32_t bits;
    uint8_t shift = 7;
    switch(eOffset)
    {
        case   12:   bits = 0x0F; break;
        case   11:   bits = 0x0E; break;
        case   10:   bits = 0x0D; break;
        case    9:   bits = 0x0C; break;
        case    8:   bits = 0x0B; break;
        case    7:   bits = 0x0A; break;
        case    6:   bits = 0x09; break;
        case    5:   bits = 0x08; break;    
        case    4:   bits = 0x07; break;
        case    3:   bits = 0x06; break;
        case    2:   bits = 0x05; break;
        case    1:   bits = 0x04; break;
        case    0:   bits = 0x03; break;
        case   -1:   bits = 0x02; break;
        case   -2:   bits = 0x01; break;
        case   -3:   bits = 0x00; break;    
    }
    bits = bits << shift;
    modifyBits(chopconf.hend, bits, &CHOPCONF_CMD);
}

void TMC2660::hystDecrement(uint8_t offDec)
{
    uint32_t bits;
    uint8_t shift = 11;
    switch(offDec)
    {
        case   64:  bits = 0x03; break;
        case   48:  bits = 0x02; break;
        case   32:  bits = 0x01; break;
        case   16:  bits = 0x00; break;
    }
    bits = bits << shift;
    modifyBits(chopconf.hdec, bits, &CHOPCONF_CMD);
}

void TMC2660::chopperMode(bool flag)
{
    uint32_t bits;
    uint8_t shift = 14;
    if (flag)
    {
        bits = 1 << shift;
    }
    else
    {
        bits = 0 << shift;
    }
    modifyBits(chopconf.chm, bits, &CHOPCONF_CMD);    
}

void TMC2660::blankTime(uint8_t blankTime)
{
    uint32_t bits;
    uint8_t shift = 15;
    switch(blankTime)
    {
        case    54:  bits = 0x03; break;
        case    36:  bits = 0x02; break;
        case    24:  bits = 0x01; break;
        case    16:  bits = 0x00; break;
    }
    bits = bits << shift;
    modifyBits(chopconf.tbl, bits, &CHOPCONF_CMD);
}

/*********************************************************************************
************************************ DRVCONF FUNCTIONS ***************************
*********************************************************************************/

void TMC2660::readMode(uint8_t rMode)
{
    uint32_t bits;
    uint8_t shift = 4;
    switch(rMode)
    {
        case     2:  bits = 0x02; break;
        case     1:  bits = 0x01; break;
        case     0:  bits = 0x00; break;
    }
    bits = bits << shift;
    modifyBits(drvconf.rdsel, bits, &DRVCONF_CMD);
}

void TMC2660::senseResScale(bool flag)
{
    uint32_t bits;
    uint8_t shift = 6;
    if (flag)
    {
        bits = 1 << shift;
    }
    else 
    {
        bits = 0 << shift;
    }
    modifyBits(drvconf.vsense, bits, &DRVCONF_CMD);
}

void TMC2660::stepMode(bool flag)
{
    uint32_t bits;
    uint8_t shift = 7;
    if (flag)
    {
        bits = 1 << shift;
    }
    else 
    {
        bits = 0 << shift;
    }
    modifyBits(drvconf.sdoff, bits, &DRVCONF_CMD);    
}

void TMC2660::motorShortTimer(uint8_t detectTime)
{
    uint32_t bits;
    uint8_t shift = 8;
    switch(detectTime)
    {
        case     3:  bits = 0x00; break;
        case     2:  bits = 0x01; break;
        case     1:  bits = 0x02; break;
        case     0:  bits = 0x03; break; 
    }
    modifyBits(drvconf.ts2g, bits, &DRVCONF_CMD);
}

void TMC2660::enableDetectGND(bool flag)
{
    uint32_t bits;
    uint8_t shift = 10;
    if (flag)
    {
        bits = 1 << shift;
    }
    else 
    {
        bits = 0 << shift;
    }
    modifyBits(drvconf.diss2g, bits, &DRVCONF_CMD);       
}

void TMC2660::slopeControlLow(uint8_t slopeLowCtrl)
{
    uint32_t bits;
    uint8_t shift = 12;
    switch(slopeLowCtrl)
    {
        case     3:  bits = 0x03; break;
        case     2:  bits = 0x02; break;
        case     1:  bits = 0x01; break;
        case     0:  bits = 0x00; break;
    }
    modifyBits(drvconf.slpl, bits, &DRVCONF_CMD);
}

void TMC2660::slopeControlHigh(uint8_t slopeHighCtrl)
{
    uint32_t bits;
    uint8_t shift = 14;
    switch(slopeHighCtrl)
    {
        case     3:  bits = 0x03; break;
        case     2:  bits = 0x02; break;
        case     1:  bits = 0x01; break;
        case     0:  bits = 0x00; break;
    }
    modifyBits(drvconf.slph, bits, &DRVCONF_CMD);
}
