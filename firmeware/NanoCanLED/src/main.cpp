#include <Arduino.h>
#include <config.h>

#include<led_strip.h>
#include <parse.h>


using namespace std;

bool readCommand();

const uint8_t cmdSize = 128;

char cmd[cmdSize];



const uint8_t LED = 13;

void setup()
{

  //LED OFf
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);


  Serial.begin(2400);
  Serial.println("Hallo!");
  initLedStrip();
  /*

  rgbwColor_t onColor;
  onColor.r = 255;

  setOn(onColor);
  */
}

bool readCommand()
{
  static uint8_t index = 0;

  while (Serial.available() > 0)
  {
      int incomingByte = Serial.read();
      if(incomingByte != -1)
      {
        char newChar = (char)incomingByte;

        Serial.print(newChar);
        if (newChar == ';')
        {
          cmd[index] = '\0';
          index = 0;
          return true;
        }

        cmd[index++] = newChar;

        if (index == cmdSize)
        {
          index = 0;
          return false;
        }
      }
  }
  return false;
}

bool checkCommand(const char* cmd,char* input,uint8_t* index)
{
  for (uint8_t i = 0; i < 128; i++)
  {
    *index = i;

    char charCmd = cmd[i];
    char charInput = input[i];

    if (charCmd == '\0' )
      return true;

    if (charInput == '\0' || charCmd != charInput)
      return false;


  }

  return false;
}

void loop()
{
  if(readCommand())
  {
    Serial.println();

    const char* onCmd = "on";
    const char* offCmd ="off";

    const char* setBackgroundColorCmd = "setBackgroundColor";

    const char* startBarCmd = "startBar";

    uint8_t index = 0;

    if (checkCommand(onCmd,cmd,&index))
    {
      setOn();
    }
    else if(checkCommand(offCmd,cmd,&index))
    {
      setOff();
    }
    else if(checkCommand(startBarCmd,cmd,&index))
    {
      startBarAnimation();
    }
    else if(checkCommand(setBackgroundColorCmd,cmd,&index))
    {
      hsvwColor_t onColor = parseColor(cmd,&index);

      setBackgroundColor(onColor);

    }
  }


  ledStripUpdateTask();
}
