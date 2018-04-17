#include "AM2320.h"
#include <Wire.h>

AM2320::AM2320()
{

}

int AM2320::Read()
{
  Wake();
  bool result = Prepare();
  if (!result)
    return 1; //Failed.

  delayMicroseconds(1550); //Wait for > 1500us

  Wire.requestFrom(ADDRESS, 8);
  memset(_buf, 0, 8);
  for (byte i = 0; i < 8; i++)
    _buf[i] = Wire.read();

  unsigned int crc = _buf[7] << 8;
  crc += _buf[6];
  
  if (crc != CRC16(_buf, 6))
    return 2; //CRC Check failed

  unsigned int humidity = (_buf[2] << 8) + _buf[3];
  _humidity = humidity / 10.0;
  
  unsigned int temperature = ((_buf[4] & 0x7F) << 8) + _buf[5];
  _temperature = temperature / 10.0;
  
  return 0;
}

void AM2320::Wake()
{
  Wire.beginTransmission(ADDRESS);
  Wire.endTransmission();
}

bool AM2320::Prepare()
{
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x03); //Function code - Read Register Data
  Wire.write(0x00); //Start address
  Wire.write(0x04); //Bytes to read
  return Wire.endTransmission(true) == 0;
}

float AM2320::Humidity()
{
  return _humidity;
}

float AM2320::Temperature()
{
  return _temperature;
}

unsigned int AM2320::CRC16(byte* ptr, byte length)
{
  unsigned short crc = 0xFFFF;
  while(length--)
  {
    crc ^= *ptr++;
    for (byte i = 0; i < 8; i++)
    {
      if ((crc & 0x01) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}

