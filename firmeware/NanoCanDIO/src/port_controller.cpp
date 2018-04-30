#include <port_controller.h>

#include <Arduino.h>

void portController::init(uint8_t port,portsettings_t* setting)
{
  _pin = port;
  _portSetting = setting;


  _strip.updateLength(0);
  _strip.setPin(_pin);
  _strip.begin();

  reset();
}

void portController::reset()
{
  switch (_portSetting->type)
  {
    case porttypes_t::Off:
      setOff();
      break;
    case porttypes_t::input:
      setInput(false);
      break;
    case porttypes_t::input_pullup:
      setInput(true);
      break;
    case porttypes_t::adc_8:
      setAdc();
      break;
    case porttypes_t::adc_10:
      setAdc();
      break;
    case porttypes_t::output:
      setOutput();
      break;
    case porttypes_t::led_strip:
      setLed();
      break;
  }

  setOff();
}

void portController::setOff()
{

}

void portController::setInput(bool pullup)
{
  if (pullup)
    pinMode(_pin, INPUT);
  else
    pinMode(_pin, INPUT_PULLUP);
}

void portController::setAdc()
{
  pinMode(_pin, INPUT);
}

void portController::setOutput()
{
  pinMode(_pin, OUTPUT);
}

void portController::setLed()
{
  pinMode(_pin, OUTPUT);

  _strip.updateLength(_portSetting->ledNumbers);
  _strip.updateType(NEO_BRG + NEO_KHZ800);
}

//Loop
void portController::loop()
{
  if (_portSetting == nullptr)
    return;

  if (_portSetting->type == porttypes_t::Off )
    return;

    switch (_portSetting->type)
    {
      case porttypes_t::input:
        loopInput();
        break;
      case porttypes_t::input_pullup:
        loopInput();
        break;
      case porttypes_t::adc_8:
        loopAdc();
        break;
      case porttypes_t::adc_10:
        loopAdc();
        break;
      case porttypes_t::output:
        loopOutput();
        break;
      case porttypes_t::led_strip:
        loopLed();
        break;
      default:
        return;
    }

}

void portController::loopInput()
{
  _portSetting->onOffState = digitalRead(_pin);
}

void portController::loopAdc()
{
  _portSetting->adcValue = analogRead(_pin);
}

void portController::loopOutput()
{
  digitalWrite(_pin, _portSetting->onOffState);
}

void portController::loopLed()
{
  if(_currentAnimation == nullptr)
    _currentAnimation = &_defaultAnimation;

  if (_oldAnimation != _currentAnimation)
    _currentAnimation->start();

  _oldAnimation = _currentAnimation;



  if(_currentAnimation->drawNext(&_strip,_portSetting))
  {
    _currentAnimation->end();
    _currentAnimation = nullptr;
  }
}
