#ifndef __LED_STRIP_H__
#define __LED_STRIP_H__

#include "led_color.h"
#include <Adafruit_NeoPixel.h>

struct settings
{
  pixelColor_t backgroundColor;
  pixelColor_t foregroundColor;
};

extern const uint8_t pinNum;
extern const uint8_t numberOfLeds;

extern const uint8_t brightLimit;

extern Adafruit_NeoPixel strip;

void initLedStrip();
void ledStripUpdateTask(void);

void setOn();
void setOff();

void startBarAnimation();
void startBarAnimation(rgbwColor_t color);

void setBackgroundColor(pixelColor_t color);
void setForegroundColor(pixelColor_t color);

void setBackgroundColor(hsvwColor_t color);
void setForegroundColor(hsvwColor_t color);


#endif
