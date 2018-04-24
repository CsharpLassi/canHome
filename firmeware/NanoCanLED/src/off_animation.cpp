#include <animation.h>
#include <led_strip.h>
#include <Arduino.h>


bool offAnimation::drawNext( Adafruit_NeoPixel *strip, settings* settings)
{
  pixelColor_t black;
  black.r = 0;
  black.g = 0;
  black.b = 0;
  black.w = 0;

  cleanUp(strip,black);
  strip->show();

  return true;
}
