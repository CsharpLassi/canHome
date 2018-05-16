#include <animation.h>
#include <Arduino.h>


bool defaultAnimation::drawNext( Adafruit_NeoPixel *strip, portsettings_t* settings)
{
  pixelColor_t showColor = settings->backgroundColor;

  bool isChanged = false;

  if(!isChanged && this->oldColor.r != showColor.r)
    isChanged = true;

  if(!isChanged && this->oldColor.g != showColor.g)
    isChanged = true;

  if(!isChanged && this->oldColor.b != showColor.b)
    isChanged = true;

  if(!isChanged && this->oldColor.w != showColor.w)
    isChanged = true;

  if(isChanged)
  {
    cleanUp(strip,showColor,settings->ledNumbers);
    strip->show();
  }
  return false;
}
