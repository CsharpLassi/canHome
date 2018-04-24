#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

//BOARD
extern const uint8_t BOARDID;
extern const uint8_t BOARDVERSION;
extern const uint8_t FIRMWAREVERSION;

const uint8_t BOARDID =1;
const uint8_t BOARDVERSION = 1;
const uint8_t FIRMWAREVERSION = 1;

extern const uint8_t numberOfLeds;
extern const uint8_t pinNum;

extern const uint8_t maxBrightness;
extern Adafruit_NeoPixel strip;

const uint8_t numberOfLeds = 100;
const uint8_t pinNum = 2;

const uint8_t maxBrightness = 255;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfLeds, pinNum, NEO_BRG + NEO_KHZ800);

#endif
