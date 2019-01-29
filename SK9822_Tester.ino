/*
      //Pin out for module
      D5  CLK   -   Red
      D7  DATA  -   Black
*/      

#include "SPI.h"
#include "apa102LEDStrip.h"
#include "colourObject.h"
#include <ESP8266WiFi.h>

const short int numLeds = 100;
const byte bytesPerLed = 4;
const byte maxValue = 64;
unsigned short int tickCnt=0, cIndex=0;

byte tempColour[3] = {0,0,0};

char colourList[9*3]={maxValue,0,0, maxValue,maxValue,0, 0,maxValue,0, 0,maxValue,maxValue, 0,0,maxValue, 0,0,0, maxValue,0,maxValue, maxValue,maxValue,maxValue, maxValue,0,0};
colourObject dynamicMultiColourBlock(maxValue, 9, colourList);
apa102LEDStrip leds = apa102LEDStrip(numLeds, bytesPerLed, 255);

void setup()
{
  WiFi.mode(WIFI_OFF);  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setFrequency(10000000);
  renderLEDs();
}


//  NODEmcu SPI APA102 LED Strip Driver code
void renderLEDs()
{
  SPI.writeBytes(leds.LEDs, leds._frameLength);
}



void loop()
{   
  dynamicMultiColourBlock.getColour(cIndex%dynamicMultiColourBlock._bandWidth, tempColour);
  leds.setPixel(0, tempColour);
  for(tickCnt=numLeds-1; tickCnt>0; tickCnt--)
  {
    leds.getPixel(tickCnt-1, tempColour);
    leds.setPixel(tickCnt, tempColour);
  }
  renderLEDs();
  delay(10);
  cIndex++;
}
