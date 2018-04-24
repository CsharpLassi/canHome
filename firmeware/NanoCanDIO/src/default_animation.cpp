#include <animation.h>
#include <led_strip.h>
#include <Arduino.h>


bool defaultAnimation::drawNext( Adafruit_NeoPixel *strip, settings* settings)
{
  pixelColor_t showColor = settings->backgroundColor;

  cleanUp(strip,showColor);
  strip->show();

  return true;
}
