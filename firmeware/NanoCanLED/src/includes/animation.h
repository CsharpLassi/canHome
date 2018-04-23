#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Adafruit_NeoPixel.h>

#include <stdint.h>
#include <led_color.h>
#include <led_strip.h>

void cleanUp(Adafruit_NeoPixel*,pixelColor_t color);

class animation
{
  public:
    virtual void start();
    virtual void end();
    virtual void drawNext(Adafruit_NeoPixel*, settings*, bool* interrupt);
};

class onAnimation : public animation
{
  public:
    uint16_t ledDelay = 0;
    void start(){ };
    void end(){ };
    void drawNext(Adafruit_NeoPixel*, settings*, bool* interrupt);
};

class barAnimation : public animation
{
  private:
    uint8_t step = 0;
    bool foregroundColorIsSet = false;
    pixelColor_t foregroundColor;

    pixelColor_t getForegroundColor(settings*);

  public:
    uint16_t ledDelay = 0;

    void setForegroundColor(pixelColor_t);

    void start();
    void end();
    void drawNext(Adafruit_NeoPixel*, settings*, bool* interrupt);
};

class offAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    void drawNext(Adafruit_NeoPixel*, settings*, bool* interrupt);
};


#endif
