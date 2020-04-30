#include <SPI.h>
#include <AccelStepper.h>

#define EN_PIN           1 // Enable
#define DIR_PIN          4 // Direction
#define STEP_PIN         3 // Step
#define CS_PIN           7 // Chip select
#define CLK_PIN          6 //CLK SELECT, leave this LOW
#define TEMP_SENS        A2 


uint32_t spi_speed = 16000000/8; // Default 2MHz

void setup() 
{
    pinMode(CS_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
    digitalWrite(CLK_PIN, LOW);
    digitalWrite(DIR_PIN, HIGH);

                                    // Enable one according to your setup
    SPI.begin();                    // SPI drivers
    // driver.sgt(STALL_VALUE);
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    char CHOPCONFToSend[3] = {0x09, 0x01, 0xB4}; //CHECKED
    char SGSCONFToSend[3]  = {0x0D, 0x00, 0x1F}; //CHECKED
    char DRVCONFToSend[3] = {0x0E, 0x00, 0x20}; //CHECKED
    char DRVCTRLToSend[3] = {0x00, 0x00, 0x03}; //CHECKED
    char SMARTENToSend[3] = {0x0A, 0x82, 0x02}; //CHECKED

    digitalWrite(CS_PIN, LOW);
    SPI.transfer(&CHOPCONFToSend, 3);
    digitalWrite(CS_PIN, HIGH);
    
    digitalWrite(CS_PIN, LOW);
    SPI.transfer (&SGSCONFToSend, 3);
    digitalWrite(CS_PIN, HIGH);

    digitalWrite(CS_PIN, LOW);
    SPI.transfer (&DRVCONFToSend, 3);
    digitalWrite(CS_PIN, HIGH);

    digitalWrite(CS_PIN, LOW);
    SPI.transfer (&DRVCTRLToSend, 3);
    digitalWrite(CS_PIN, HIGH);

    digitalWrite(CS_PIN, LOW);
    SPI.transfer (&SMARTENToSend, 3);
    digitalWrite(CS_PIN, HIGH);

    SPI.endTransaction();
}

//bool shaft = false;

void loop() 
{
  // Run 5000 steps and switch direction in software
  // for (uint16_t i = 5000; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    // Serial.println("1");
    // delayMicroseconds(160);
    delayMicroseconds(20);
    digitalWrite(STEP_PIN, LOW);
    // Serial.println("2");
    delayMicroseconds(20);
}
