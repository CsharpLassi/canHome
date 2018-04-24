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
    virtual bool drawNext(Adafruit_NeoPixel*, settings*);
};

class defaultAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, settings*);
};

class onAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, settings*);
};

class barAnimation : public animation
{
  private:
    uint8_t step = 0;
    bool foregroundColorIsSet = false;
    
  public:


    void start();
    void end();
    bool drawNext(Adafruit_NeoPixel*, settings*);
};

class offAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, settings*);
};


#endif
