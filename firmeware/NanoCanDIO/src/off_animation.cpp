#include <animation.h>
#include <Arduino.h>


bool offAnimation::drawNext( Adafruit_NeoPixel *strip, portsettings_t* settings)
{
  pixelColor_t black;
  black.r = 0;
  black.g = 0;
  black.b = 0;
  black.w = 0;

  cleanUp(strip,black,settings->ledNumbers);
  strip->show();

  return true;
}
