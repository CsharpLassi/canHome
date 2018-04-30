#include <animation.h>
#include <Arduino.h>


bool defaultAnimation::drawNext( Adafruit_NeoPixel *strip, portsettings_t* settings)
{
  pixelColor_t showColor = settings->backgroundColor;

  cleanUp(strip,showColor,settings->ledNumbers);
  strip->show();

  return true;
}
