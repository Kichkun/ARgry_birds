#include <SoftwareSerial.h>
#include <Wire.h>
#include "MMA7660.h"

MMA7660 accelemeter;
SoftwareSerial EEBlue(2, 3); // RX | TX
String state = "0";
void setup()
{
  accelemeter.init();
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); 
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
      state = EEBlue.readString();
      //Serial.write(state);
      //char result[8]; // Buffer big enough for 7-character float
      //dtostrf(ax, 6, 2, result); // Leave room for too large numbers!
    }
    char result[4];
    //nothing but 0 to 1 while detected
    // 0 - 4 : 1 - red, 2 - blue, 3 - yellow, 4 - white, 0 - off
    //char out[17] = {dtostrf(ax, 3, 2, result), ';', dtostrf(ay, 3, 2, result1), ';',dtostrf(az, 3, 2, result2)};
    //Serial.write(out);
    float res = sqrt(x*x + y*y + z*z);
    if (res>50)
      EEBlue.write(dtostrf(res/100, 2, 2, result));
    if (state == "0"){
       analogWrite(10, 0);
       analogWrite(11, 0);
       analogWrite(12, 0);
    }
    if (state == "1"){
       analogWrite(10, 255);
       analogWrite(11, 0);
       analogWrite(12, 0);
    }
    if (state == "2"){
       analogWrite(10, 0);
       analogWrite(11, 255);
       analogWrite(12, 0);
    }
  // Feed all data from termial to bluetooth
  if (Serial.available())
    {
    EEBlue.write(Serial.read());
    }
  //String a = String(ax)+";"+String(ay)+";"+String(az);
  //EEBlue.println(a);
  Serial.flush();
}
