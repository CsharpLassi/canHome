#include <Arduino.h>
#include <stdint.h>

#include "can_controller.h"
#include "can_package.h"

#include <parse.h>


#include "board.h"

using namespace std;

bool readCommand();
void executeCommand(canPackage_t*);

const uint8_t cmdStringSize = 128;
char cmdString[cmdStringSize];



canStringCommand commands[] =
{
  {.command = "set", .commandId = canCommand::set},
  {.command = "get", .commandId = canCommand::get},
  {.command = "save", .commandId = canCommand::saveSettings},
  {.command = "monitor", .commandId = canCommand::monitor},
  {.command = "on", .commandId = canCommand::on},
  {.command = "off", .commandId = canCommand::off},
};

bool monitor = true;

void setup()
{
  CanController::setupController();

  canSettings_t currentSettings = CanController::getSettings();

  CanController::initCan();


  boardSetup();


  Serial.begin(2400);

  Serial.print("CanClient V");
  Serial.println(currentSettings.canVersion);

  Serial.print("Board ");
  Serial.print(currentSettings.boardId);

  Serial.print(" V");
  Serial.println(currentSettings.boardVersion);

  Serial.print("Firmeware V");
  Serial.println(currentSettings.firmewareVersion);

  Serial.print("Id ");
  Serial.println(currentSettings.deviceId);

  Serial.println("#[on/off] deviceId [port];");
  Serial.println("#monitor;");
  Serial.println("#[set/get] deviceId parameter [d0/Port] d1 d2 ...;");
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
          cmdString[index] = '\0';
          index = 0;
          return true;
        }

        cmdString[index++] = newChar;

        if (index ==  cmdStringSize)
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
  const uint8_t cmdSize = sizeof(commands)/sizeof(canStringCommand);

  if(readCommand())
  {
    Serial.println();
    bool cmdFounded = false;
    uint8_t index = 0;

    canPackage_t package;

    for (register uint8_t i = 0; i < cmdSize; i++)
    {
      canStringCommand command = commands[i];
      if (checkCommand(command.command,cmdString,&index))
      {
        package = parsePackage(cmdString,&index);
        package.cmd = (uint16_t)command.commandId;
        cmdFounded = true;
        break;
      }

    }

    if (cmdFounded)
    {
      CanController::executeCommand(&package);

      if (package.deviceId != 0)
        CanController::sendCommand(&package);
    }
  }

  CanController::loopCan();

  boardLoop();
}
