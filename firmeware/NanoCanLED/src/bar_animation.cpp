#include <animation.h>
#include <led_strip.h>
#include <Arduino.h>

void barAnimation::start()
{
  step = 0;
}


bool barAnimation::drawNext(Adafruit_NeoPixel *strip,settings* settings)
{
    pixelColor_t foregroundColor =  settings->foregroundColor;
    pixelColor_t backgroundColor =  settings->backgroundColor;


    cleanUp(strip, backgroundColor);

    strip->setPixelColor(step, foregroundColor.r , foregroundColor.g, foregroundColor.b);

    strip->show();

    step = (step+ 1)% numberOfLeds;

    return false;
}

void barAnimation::end()
{

}
