#include <SoftwareSerial.h>
#include <Wire.h>
#include "MMA7660.h"

MMA7660 accelemeter;
SoftwareSerial EEBlue(2, 3); // RX | TX
 
void setup()
{
  accelemeter.init(); 
  Serial.begin(9600);
  EEBlue.begin(9600);  //Baud Rate for command Mode. 
  Serial.println("Enter AT commands!");
}
 
void loop()
{
  int8_t x;
  int8_t y;
  int8_t z;
  float ax,ay,az;
  accelemeter.getXYZ(&x,&y,&z);
  accelemeter.getAcceleration(&ax,&ay,&az);
  

  // Feed any data from bluetooth to Terminal.
  if (EEBlue.available())
    {
      Serial.write(EEBlue.read());
    }
    char result[4];
    //nothing but 0 to 1 while detected
    // 0 - 4 : 1 - red, 2 - blue, 3 - yellow, 4 - white, 0 - off
    float res = sqrt(x*x + y*y + z*z);
    if (res>50)
      EEBlue.write(dtostrf(res/100, 2, 2, result));
  if (Serial.available())
    {
    EEBlue.write(Serial.read());
    }
 }
