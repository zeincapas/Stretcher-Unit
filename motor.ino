#include <SPI.h>
#include <AccelStepper.h>
#include "TMCDriver.h"

TMC2660 driver(7, 1); //(CS_PIN, EN_PIN)

void setup() 
{
  driver.init();

  // //DRVCTRL settings 
  // driver.doubleStepping(1);
  // driver.stepInterpolation(1);
  // driver.setMicroStep(8);

  // //CHOPCONF settings
  // driver.blankTime(54);
  // driver.chopperMode(1);
  // driver.hystEnd(0);
  // driver.hystStart(6);
  // driver.hystDecrement(64);
  // driver.slowDecayTime(11);

  // // DRVCONF settings
  // driver.readMode(1);
  // driver.senseResScale(0);
  // driver.stepMode(0);
  // driver.motorShortTimer(3);
  // driver.enableDetectGND(0);
  // driver.slopeControlLow(0);
  // driver.slopeControlHigh(3);

  // //SMARTEN settings
  // driver.coilLowerThreshold(0);
  // driver.coilIncrementSize(1);
  // driver.coilUpperThreshold(0);
  // driver.coilDecrementSpd(32);
  // driver.minCoilCurrent(0);

  //SGCSCONF settings
  driver.currentScale(0);
  driver.stallGrdThresh(4);
  driver.filterMode(0);

  //Write to stepper driver
  // driver.write(&driver.CHOPCONF_CMD);
  // driver.write(&driver.DRVCTRL_0_CMD);
  // driver.write(&driver.DRVCONF_CMD);
  // driver.write(&driver.SMARTEN_CMD);
  driver.write(&driver.SGCSCONF_CMD);

}

void loop() {
  while(1);
}

// #include <SPI.h>

// #define EN_PIN           1 // Enable
// #define DIR_PIN          4 // Direction
// #define STEP_PIN         3 // Step
// #define CS_PIN           7 // Chip select
// #define CLK_PIN          6 //CLK SELECT, leave this LOW
// #define TEMP_SENS        A2 


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

//   // digitalWrite(CS_PIN, LOW);
//   // SPI.transfer (SMARTENToSend, 3);
//   // digitalWrite(CS_PIN, HIGH);

//   SPI.endTransaction();
// }

// //bool shaft = false;

// void loop() {
//   // Run 5000 steps and switch direction in software
//   // for (uint16_t i = 5000; i>0; i--) {
//     digitalWrite(STEP_PIN, HIGH);
//     // Serial.println("1");
//     delayMicroseconds(160);
//     digitalWrite(STEP_PIN, LOW);
//     // Serial.println("2");
//     delayMicroseconds(160);
// // }
  
// }
