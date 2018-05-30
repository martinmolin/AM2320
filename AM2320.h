#ifndef AM2320_H
#define AM2320_H

#include <Arduino.h>

#define ADDRESS 0x5C

class AM2320
{
  public:
    AM2320();
    float Temperature();
    float Humidity();
    int Read();
  private:
    float _temperature;
    float _humidity;
    byte _buf[8];

    void Wake();
    bool Prepare();
    unsigned int CRC16(byte* ptr, byte length);
};

#endif
