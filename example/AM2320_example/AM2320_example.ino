#include <Wire.h>
#include "AM2320.h"

AM2320 am2320;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  switch(am2320.Read())
  {
    case 0:
      Serial.print("Humidity: ");
      Serial.print(am2320.Humidity());
      Serial.print("%, Temperature: ");
      Serial.print(am2320.Temperature());
      Serial.println("*C");
      break;
    case 1:
      Serial.println("Could not read sensor");
      break;
    case 2:
      Serial.println("CRC mismatch");
      break;
  }
  delay(1000);
}
