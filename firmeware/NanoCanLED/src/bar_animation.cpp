#include <animation.h>
#include <led_strip.h>
#include <Arduino.h>

void barAnimation::start()
{
  step = 0;
}

void barAnimation::setForegroundColor(pixelColor_t useColor)
{
  foregroundColorIsSet = true;
  foregroundColor = useColor;
}

pixelColor_t barAnimation::getForegroundColor(settings* settings)
{
  if(foregroundColorIsSet)
    return foregroundColor;
  return settings->foregroundColor;
}

bool barAnimation::drawNext(Adafruit_NeoPixel *strip,settings* settings)
{


    if (ledDelay == 0)
      ledDelay = 100;


    pixelColor_t backgroundColor;
    pixelColor_t foregroundColor;

    return true;
}

void barAnimation::end()
{
  foregroundColorIsSet = false;
}
