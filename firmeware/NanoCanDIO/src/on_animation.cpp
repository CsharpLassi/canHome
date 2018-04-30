#include <animation.h>
#include <Arduino.h>


bool onAnimation::drawNext(Adafruit_NeoPixel* strip,portsettings_t* settings)
{
  pixelColor_t showColor = settings->backgroundColor;

  for (uint8_t i = 0; i < settings->ledNumbers; i++)
  {
    strip->setPixelColor(i, showColor.r, showColor.g, showColor.b);

    strip->show();
    delay(settings->delay);
  }

  return true;
}
