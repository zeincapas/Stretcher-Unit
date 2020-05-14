#include <SPI.h>
#include <AccelStepper.h>
#include "TMCDriver.h"

#define DIR_PIN          4 // Direction
#define STEP_PIN         3 // Step
#define CS_PIN           7 // Chip select

TMC2660 driver(CS_PIN); //(CS_PIN, EN_PIN)
uint32_t readVal;

void setup() 
{
  Serial.begin(9600);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  driver.init();

  // DRVCTRL settings 
  driver.doubleStepping(0);
  driver.stepInterpolation(0);
  driver.setMicroStep(64);

  //CHOPCONF settings
  driver.blankTime(24);
  driver.chopperMode(0);
  driver.hystEnd(5);
  driver.hystStart(6);
  driver.hystDecrement(32);
  driver.slowDecayTime(5);

  // DRVCONF settings
  driver.readMode(0);
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

  //Write the constructed bitfields to the driver
  driver.pushCommands();
}


void loop() 
{
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(15);

    readVal = driver.read();
    driver.translateResponse(readVal);
    driver.printResponse();
}
