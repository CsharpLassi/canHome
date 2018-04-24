#ifndef __LED_COLOR_H__
#define __LED_COLOR_H__

#include <stdint.h>
#include <WString.h>


using namespace std;

struct rgbwColor_t
{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  uint8_t w;
};

struct hsvwColor_t
{
  float h;
  float s;
  float v;

  uint8_t w;
};

struct pixelColor_t
{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  uint8_t w;
};

extern const uint8_t maxBrightness;


hsvwColor_t convertToHSV(rgbwColor_t color);
hsvwColor_t convertToHSV(uint8_t,uint8_t,uint8_t);

pixelColor_t createPWMColor(rgbwColor_t);
pixelColor_t createPWMColor(hsvwColor_t);



#endif
