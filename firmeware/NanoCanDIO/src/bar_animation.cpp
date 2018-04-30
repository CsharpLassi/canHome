#include <animation.h>
#include <Arduino.h>

void barAnimation::start()
{
  step = 0;
}


bool barAnimation::drawNext(Adafruit_NeoPixel *strip,portsettings_t* settings)
{
    pixelColor_t foregroundColor =  settings->foregroundColor;
    pixelColor_t backgroundColor =  settings->backgroundColor;


    cleanUp(strip, backgroundColor,settings->ledNumbers);

    strip->setPixelColor(step, foregroundColor.r , foregroundColor.g, foregroundColor.b);

    strip->show();

    step = (step+ 1)% settings->ledNumbers;

    return false;
}

void barAnimation::end()
{

}
