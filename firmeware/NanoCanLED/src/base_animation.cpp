#include <animation.h>

void cleanUp(Adafruit_NeoPixel* strip,pixelColor_t color)
{
  for (uint8_t i = 0; i < numberOfLeds; i++)
  {
    strip->setPixelColor(i,color.r,color.g,color.b);
  }
  strip->show();
}
