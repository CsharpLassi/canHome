#ifndef __PORT_CONTROLLER_H__
#define __PORT_CONTROLLER_H__

#include <Adafruit_NeoPixel.h>
#include "port_setting.h"

#include <animation.h>

class portController
{
  private:
    uint8_t _pin;
    portsettings_t* _portSetting = nullptr;

    Adafruit_NeoPixel _strip;
    animation* _currentAnimation = nullptr;
    animation* _oldAnimation = nullptr;

    defaultAnimation _defaultAnimation;
    offAnimation _offAnimation;

    bool oldInput;

    void setOff();
    void setInput(bool pullup);
    void setAdc();
    void setOutput();
    void setLed();

    void loopInput();
    void loopAdc();
    void loopOutput();
    void loopLed();

  public:
    bool onOffState;

    void init(uint8_t port,portsettings_t*);
    void reset();
    void loop();
};

#endif
