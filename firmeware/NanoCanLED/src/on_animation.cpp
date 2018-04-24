#include <animation.h>
#include <led_strip.h>
#include <Arduino.h>


bool onAnimation::drawNext(Adafruit_NeoPixel* strip,settings* settings)
{
  pixelColor_t showColor = settings->backgroundColor;

  for (uint8_t i = 0; i < numberOfLeds; i++)
  {
    strip->setPixelColor(i, showColor.r, showColor.g, showColor.b);

    strip->show();
    delay(ledDelay);
  }

  return true;
}
