#include <Arduino.h>
#include <config.h>

#include<led_strip.h>
#include <parse.h>


using namespace std;

bool readCommand();


String* command;

const uint8_t LED = 13;

void setup()
{

  //LED OFf
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  Serial.println("Hallo!");
  initLedStrip();

  command = new String();
  /*

  rgbwColor_t onColor;
  onColor.r = 255;

  setOn(onColor);
  */
}

bool readCommand()
{
  if (Serial.available() > 0)
  {
      int incomingByte = Serial.read();
      if(incomingByte != -1)
      {
        char newChar = (char)incomingByte;
        Serial.print(newChar);
        if (newChar == ';')
          return true;
        *command += newChar;

      }
  }
  return false;
}

void loop()
{
  if(readCommand())
  {

    Serial.println();
    if (command->startsWith("on"))
    {
      uint16_t index = 2;
      hsvwColor_t onColor = parseColor(command,&index);

      Serial.println(String(onColor.h) + ";" + String(onColor.s) + ";" + String(onColor.v));

      setBackgroundColor(onColor);
      setOn();
    }
    else if(command->startsWith("off"))
    {
      setOff();
    }

    command = new String();
  }

  ledStripUpdateTask();
}
