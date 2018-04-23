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

void barAnimation::drawNext(Adafruit_NeoPixel *strip,settings* settings,bool* interrupt)
{


    if (ledDelay == 0)
      ledDelay = 100;


    pixelColor_t backgroundColor;
    pixelColor_t foregroundColor;

    while (!(*interrupt))
    {
      backgroundColor = settings->backgroundColor;
      foregroundColor = getForegroundColor(settings);

      cleanUp(strip,backgroundColor);

      strip->setPixelColor(step,foregroundColor.r,foregroundColor.g,foregroundColor.b);
      step = (step +1) %numberOfLeds;



      strip->show();
      delay(ledDelay);
    }
}

void barAnimation::end()
{
  foregroundColorIsSet = false;
}
