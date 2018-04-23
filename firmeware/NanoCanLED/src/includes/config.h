#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

extern const uint8_t numberOfLeds;
extern const uint8_t pinNum;

extern const uint8_t maxBrightness;
extern Adafruit_NeoPixel strip;

const uint8_t numberOfLeds = 100;
const uint8_t pinNum = 2;

const uint8_t maxBrightness = 255;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfLeds, pinNum, NEO_BRG + NEO_KHZ800);

#endif
