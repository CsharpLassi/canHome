#include <port_controller.h>
#include "can_controller.h"

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
  oldInput = false;
  onOffState = _portSetting->defaultOnOffState;


  switch (_portSetting->type)
  {
    case porttypes_t::Off:
      setOff();
      return;
    case porttypes_t::input:
      setInput(false);
      return;
    case porttypes_t::input_pullup:
      setInput(true);
      return;
    case porttypes_t::adc_8:
      setAdc();
      return;
    case porttypes_t::adc_10:
      setAdc();
      return;
    case porttypes_t::output:
      setOutput();
      return;
    case porttypes_t::led_strip:
      setLed();
      return;

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
  if(!onOffState)
    return;

  bool input = digitalRead(_pin);

  if(oldInput != input)
  {
    if (input)
      CanController::sendAndExecuteCommand(canCommand::TriggerOn);
    else
      CanController::sendAndExecuteCommand(canCommand::TriggerOff);
  }

  oldInput = input;
}

void portController::loopAdc()
{
  if(!onOffState)
    return;
}

void portController::loopOutput()
{
  if(!onOffState)
    return;
}

void portController::loopLed()
{
  if(!onOffState && _currentAnimation == nullptr)
    return;

  if(_currentAnimation == nullptr)
  {
    CanController::sendAndExecuteCommand(canCommand::TriggerOn);
    _currentAnimation = &_defaultAnimation;
  }

  if (_oldAnimation != _currentAnimation)
    _currentAnimation->start();

  _oldAnimation = _currentAnimation;

  if(!onOffState)
    _currentAnimation = &_offAnimation;

  if(_currentAnimation->drawNext(&_strip,_portSetting))
  {
    _currentAnimation->end();
    _currentAnimation = nullptr;
    CanController::sendAndExecuteCommand(canCommand::TriggerOff);
  }
}
