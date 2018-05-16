#include <Arduino.h>
#include <config.h>

#include<port_controller.h>

#include <parse.h>

#include "can_controller.h"
#include "can_package.h"
#include "can_eeprom.h"

portController ports[PORTCOUNT];
portsettings_t portSettings[PORTCOUNT];

uint8_t portPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

const uint8_t LED = 13;

void boardUpdateEEPROM()
{
  for (uint8_t i = 0; i < PORTCOUNT; i++)
    dataWrite<portsettings_t>(i+1,&portSettings[i]);
}

void boardSetup()
{
  //LED OFf
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  for (uint8_t i = 0; i < PORTCOUNT; i++)
    portSettings[i] = dataRead<portsettings_t>(i+1);

  for (size_t i = 0; i < PORTCOUNT; i++)
    ports[i].init(portPins[i],&portSettings[i]);

  digitalWrite(LED, LOW);
}

void boardLoop()
{
  for (size_t i = 0; i < PORTCOUNT; i++)
    ports[i].loop();
}

void receiveMessage(canPackage_t* package)
{
  uint8_t port = package->parameters[0];
  if( port == 0 || port > PORTCOUNT)
    return;

  port-=1;
  if(package->cmd == (uint16_t) canCommand::on)
  {
    ports[port].onOffState = true;
  }
  else if (package->cmd == (uint16_t) canCommand::off)
  {
    ports[port].onOffState = false;
  }
}

void receiveSetMessage(canSetPackage_t* package)
{
  uint8_t port = package->parameters[0];
  if( port == 0 || port > PORTCOUNT)
    return;

  port-=1;
  if(package->parameter == canParameter::setMode)
  {
    uint8_t type = package->parameters[1];
    portSettings[port].type = (porttypes_t)type;
    portSettings[port].ledNumbers = package->parameters[2];
    ports[port].reset();
  }
  else if (package->parameter == canParameter::backgroundColor || package->parameter == canParameter::color )
  {
    uint8_t r,g,b;
    r = package->parameters[1];
    g = package->parameters[2];
    b = package->parameters[3];

    Serial.println("Set new Color");
    portSettings[port].backgroundColor = createPWMColor({.r = r,.g = g, .b = b});
  }
}
