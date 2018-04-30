#include <animation.h>

void cleanUp(Adafruit_NeoPixel* strip,pixelColor_t color,uint16_t ledNumbers)
{
  for (uint8_t i = 0; i < ledNumbers; i++)
  {
    strip->setPixelColor(i,color.r,color.g,color.b);
  }
}
