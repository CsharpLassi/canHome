#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Adafruit_NeoPixel.h>

#include <stdint.h>
#include <led_color.h>
#include <port_setting.h>

void cleanUp(Adafruit_NeoPixel*,pixelColor_t color,uint16_t ledNumber);

class animation
{
  public:
    virtual void start();
    virtual void end();
    virtual bool drawNext(Adafruit_NeoPixel*, portsettings_t*);
};

class defaultAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, portsettings_t*);
};

class onAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, portsettings_t*);
};

class barAnimation : public animation
{
  private:
    uint8_t step = 0;
    bool foregroundColorIsSet = false;

  public:


    void start();
    void end();
    bool drawNext(Adafruit_NeoPixel*, portsettings_t*);
};

class offAnimation : public animation
{
  public:
    void start(){ };
    void end(){ };
    bool drawNext(Adafruit_NeoPixel*, portsettings_t*);
};


#endif
