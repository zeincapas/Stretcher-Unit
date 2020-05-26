#include <SPI.h>
#include <AccelStepper.h>
#include "TMCDriver.h"

#define DIR_PIN          4 // Direction
#define STEP_PIN         3 // Step
#define CS_PIN           7 // Chip select

TMC2660 driver(CS_PIN, 5); //(CS_PIN, EN_PIN)

uint32_t currentTime;
uint32_t oldTime = 0;
uint32_t switchPeriod = 4000;

void setup() 
{
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, HIGH);
  driver.init();

  // DRVCTRL settings 
  driver.doubleStepping(0);
  driver.stepInterpolation(0);
  driver.setMicroStep(1);

  //CHOPCONF settings
  driver.blankTime(24);
  driver.chopperMode(1);
  driver.hystEnd(5);
  driver.hystStart(6);
  driver.hystDecrement(32);
  driver.slowDecayTime(3);

  // DRVCONF settings
  driver.readMode(1);
  driver.senseResScale(0);
  driver.stepMode(0);
  driver.motorShortTimer(2);
  driver.enableDetectGND(0);
  driver.slopeControlLow(2);
  driver.slopeControlHigh(2);

  //SMARTEN settings
  driver.coilLowerThreshold(0);
  driver.coilIncrementSize(8);
  driver.coilUpperThreshold(15);
  driver.coilDecrementSpd(8);
  driver.minCoilCurrent(0);

  //SGCSCONF settings
  driver.currentScale(31);
  driver.stallGrdThresh(60);
  driver.filterMode(0);

  //Write the constructed bitfields to the driver
  driver.pushCommands();
}


void loop() 
{
    currentTime = millis();
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);

    if(currentTime - oldTime > switchPeriod)
    {
      digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
      delay(2000);
      oldTime = millis();
    }
}
