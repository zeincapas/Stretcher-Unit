#include <SPI.h>
#include <AccelStepper.h>
#include "TMCDriver.h"

#define DIR_PIN          4 // Direction
#define STEP_PIN         3 // Step
#define CS_PIN           7 // Chip select

TMC2660 driver(CS_PIN, 1); //(CS_PIN, EN_PIN)

void setup() 
{
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  driver.init();

  // DRVCTRL settings 
  driver.doubleStepping(0);
  driver.stepInterpolation(0);
  driver.setMicroStep(32);

  //CHOPCONF settings
  driver.blankTime(24);
  driver.chopperMode(0);
  driver.hystEnd(5);
  driver.hystStart(6);
  driver.hystDecrement(32);
  driver.slowDecayTime(5);

  // DRVCONF settings
  driver.readMode(1);
  driver.senseResScale(0);
  driver.stepMode(0);
  driver.motorShortTimer(2);
  driver.enableDetectGND(0);
  driver.slopeControlLow(2);
  driver.slopeControlHigh(2);

  //SMARTEN settings
  driver.coilLowerThreshold(8);
  driver.coilIncrementSize(8);
  driver.coilUpperThreshold(8);
  driver.coilDecrementSpd(8);
  driver.minCoilCurrent(0);

  //SGCSCONF settings
  driver.currentScale(25);
  driver.stallGrdThresh(0);
  driver.filterMode(0);

  // Write to stepper driver
  driver.write(&driver.CHOPCONF_CMD);
  driver.write(&driver.DRVCTRL_0_CMD);
  driver.write(&driver.DRVCONF_CMD);
  driver.write(&driver.SMARTEN_CMD);
  driver.write(&driver.SGCSCONF_CMD);

}

// uint32_t spi_speed = 16000000/8; // Default 2MHz

// void setup() {
//   pinMode(CS_PIN, OUTPUT);
//   pinMode(EN_PIN, OUTPUT);
//   pinMode(STEP_PIN, OUTPUT);
//   pinMode(DIR_PIN, OUTPUT);
//   digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
//   digitalWrite(CLK_PIN, LOW);

//                                   // Enable one according to your setup
//   SPI.begin();                    // SPI drivers
//   // driver.sgt(STALL_VALUE);
//   SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
//   char CHOPCONFToSend[3] = {0x9, 0x1, 0xB4}; //CHECKED
//   char SGSCONFToSend[3]  = {0xD, 0x0, 0x1F}; //CHECKED
//   char DRVCONFToSend[3] = {0xE, 0x0, 0x0}; //CHECKED
//   char DRVCTRLToSend[3] = {0x0, 0x0, 0x0}; //CHECKED
//   char SMARTENToSend[3] = {0xA, 0x82, 0x2}; //CHECKED

//   digitalWrite(CS_PIN, LOW);
//   SPI.transfer(&CHOPCONFToSend, 3);
//   digitalWrite(CS_PIN, HIGH);
  
//   digitalWrite(CS_PIN, LOW);
//   SPI.transfer (&SGSCONFToSend, 3);
//   digitalWrite(CS_PIN, HIGH);

//   digitalWrite(CS_PIN, LOW);
//   SPI.transfer (&DRVCONFToSend, 3);
//   digitalWrite(CS_PIN, HIGH);

//   digitalWrite(CS_PIN, LOW);
//   SPI.transfer (&DRVCTRLToSend, 3);
//   digitalWrite(CS_PIN, HIGH);

//   digitalWrite(CS_PIN, LOW);
//   SPI.transfer (SMARTENToSend, 3);
//   digitalWrite(CS_PIN, HIGH);

//   SPI.endTransaction();
// }

void loop() 
{
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);
}
