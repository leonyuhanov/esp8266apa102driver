/*
  This is intended for use with a NodeMCU V0.9 & V1.0 Modules or any ESP8266 Module
  This will drive a APA102/102C strip
  This code is intende to be used with 1 extra Pixel connected as close as possible to the ESP8266 as a booster pixel
  The ESP8266 MUST be driven with +5v for this to work
  
  Pinout for connectivity:
  
  Gnd-> Gound Pin of APA102 strip
  D5 -> Clock pin of APA102 Strip
  D7 -> Data Pin of APA102 Strip
  VIN -> +5v pin of APA102 Strip
  
  This will set all pixels in the strip to RED, GREEN, BLUE, WHITE and OFF with a 1 second delay in between each colour.
*/

#include "SPI.h"

//Number if Pixels in your strip
const short int numLeds = 144;
const byte bytesPerLED = 4;
//Size in BYTES of the end frame
const short int endFrames = round( (((numLeds+1)/2)/8)*bytesPerLED ) ;
/*
SPI Frame length is the total bytes required including:
  Start Frame = 4 x bytes (each set to 255) + 
  4 x Bytes for the BOOSTER Pixel + 
  numLEDs*bytesPerLED +
  endFrames (each byte needs to be set to 0)
*/
const short int frameLength = ((2+numLeds)*bytesPerLED)+endFrames;
byte LEDs[frameLength];
short int ledIndex=0;
byte maxBrightness = 255;
short int colIndex=0;
byte currentCol[3] = {0,0,0};

void setup() 
{
  //Start Frame
  LEDs[0] = 0;
  LEDs[1] = 0;
  LEDs[2] = 0;
  LEDs[3] = 0;
  //Booster LED
  LEDs[4] = maxBrightness;
  LEDs[5] = 0;
  LEDs[6] = 0;
  LEDs[7] = 0;
  //Clear all the LEDs in the strip to 0
  for(ledIndex=bytesPerLED; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    LEDs[ledIndex] = maxBrightness;
    LEDs[ledIndex+1] = 0;
    LEDs[ledIndex+2] = 0;
    LEDs[ledIndex+3] = 0;
  }
  //Set the end frame bytes to 0
  for(ledIndex=frameLength-endFrames; ledIndex<frameLength; ledIndex+=bytesPerLED)
  {
    LEDs[ledIndex] = 0;
    LEDs[ledIndex+1] = 0;
    LEDs[ledIndex+2] = 0;
    LEDs[ledIndex+3] = 0;
  }
  //Initialise the SPI
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  //Dumpt data to the strip
  renderLEDs();
}

// the loop function runs over and over again forever
void loop() 
{
  //sets all LEDs to RED
  currentCol[0]=255;
  currentCol[1]=0;
  currentCol[2]=0;
  for(ledIndex=8; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    //LEDs[ledIndex] = maxBrightness; //Global Brightess Byte for this Pixel
    LEDs[ledIndex+1] = currentCol[2]; //Blue pixel
    LEDs[ledIndex+2] = currentCol[1]; //Green pixel
    LEDs[ledIndex+3] = currentCol[0]; //Red pixel
  }
  renderLEDs();
  delay(1000);
  //sets all LEDs to Green
  currentCol[0]=0;
  currentCol[1]=255;
  currentCol[2]=0;
  for(ledIndex=8; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    //LEDs[ledIndex] = maxBrightness; //Global Brightess Byte for this Pixel
    LEDs[ledIndex+1] = currentCol[2]; //Blue pixel
    LEDs[ledIndex+2] = currentCol[1]; //Green pixel
    LEDs[ledIndex+3] = currentCol[0]; //Red pixel
  }
  renderLEDs();
  delay(1000);
  //sets all LEDs to BLUE
  currentCol[0]=0;
  currentCol[1]=0;
  currentCol[2]=255;
  for(ledIndex=8; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    //LEDs[ledIndex] = maxBrightness; //Global Brightess Byte for this Pixel
    LEDs[ledIndex+1] = currentCol[2]; //Blue pixel
    LEDs[ledIndex+2] = currentCol[1]; //Green pixel
    LEDs[ledIndex+3] = currentCol[0]; //Red pixel
  }
  renderLEDs();
  delay(1000);
  //sets all LEDs to WHITE
  currentCol[0]=255;
  currentCol[1]=255;
  currentCol[2]=255;
  for(ledIndex=8; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    //LEDs[ledIndex] = maxBrightness; //Global Brightess Byte for this Pixel
    LEDs[ledIndex+1] = currentCol[2]; //Blue pixel
    LEDs[ledIndex+2] = currentCol[1]; //Green pixel
    LEDs[ledIndex+3] = currentCol[0]; //Red pixel
  }
  renderLEDs();
  delay(1000);
  //sets all LEDs to BLACK/OFF
  currentCol[0]=0;
  currentCol[1]=0;
  currentCol[2]=0;
  for(ledIndex=8; ledIndex<frameLength-endFrames; ledIndex+=bytesPerLED)
  {
    //LEDs[ledIndex] = maxBrightness; //Global Brightess Byte for this Pixel
    LEDs[ledIndex+1] = currentCol[2]; //Blue pixel
    LEDs[ledIndex+2] = currentCol[1]; //Green pixel
    LEDs[ledIndex+3] = currentCol[0]; //Red pixel
  }
  renderLEDs();
  delay(1000);
}

void renderLEDs()
{
    short int LEDCounter = 0;
    for(LEDCounter=0; LEDCounter<frameLength; LEDCounter++)
    {
     SPI.transfer(LEDs[LEDCounter]); 
    } 
}
