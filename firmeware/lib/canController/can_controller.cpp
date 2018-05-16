#include "can_controller.h"
#include "can_eeprom.h"
#include "board.h"

#include <EEPROM.h>

#include <SPI.h>
#include <mcp2515.h>

bool monitorMode;

MCP2515 mcp2515(10);
struct can_frame receiveMsg;
struct can_frame sendMsg;

canSettings_t currentSettings;



void CanController::initCan()
{
  //monitorMode = true;
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS,MCP_16MHZ);
  //mcp2515.setLoopbackMode();
  mcp2515.setNormalMode();

  sendInfoFrame(canCommand::boot);
}

void CanController::setupController()
{
  currentSettings = dataRead<canSettings_t>(0);
  if (currentSettings.canVersion == 0 || currentSettings.canVersion == 255)
  {
    updateEEPROM();
    boardUpdateEEPROM();
  }
  else if(currentSettings.firmewareVersion != FIRMWAREVERSION)
  {
    updateEEPROM();
    boardUpdateEEPROM();
  }
}

canSettings_t CanController::getSettings()
{
  return currentSettings;
}

void CanController::sendInfoFrame(canCommand cmd)
{
  if (currentSettings.deviceId == 0)
    return;

  canPackage_t infoPackage;
  infoPackage.cmd = (uint16_t)cmd;
  infoPackage.extendpackageFlags = EXTEND_PACKAGE_FLAG_OWN_ID;
  infoPackage.deviceId = currentSettings.deviceId;
  infoPackage.length = 6;

  uint16_t deviceId = currentSettings.deviceId;

  infoPackage.parameters[0] = deviceId >> 8;
  infoPackage.parameters[1] = deviceId & 0xFF;
  infoPackage.parameters[2] = CANVERSION;
  infoPackage.parameters[3] = BOARDID;
  infoPackage.parameters[4] = BOARDVERSION;
  infoPackage.parameters[5] = FIRMWAREVERSION;

  CanController::sendAndExecuteCommand(&infoPackage);
}

void CanController::loopCan()
{
  uint8_t state =  mcp2515.readMessage(&receiveMsg);
  if (state == MCP2515::ERROR_OK)
  {
    canPackage_t receivePackage;

    for (size_t i = 0; i < 8; i++)
      receivePackage.parameters[i] = 0;

    if(receiveMsg.can_id & CAN_EFF_FLAG)
    {
      receivePackage.cmd = (uint16_t) ((receiveMsg.can_id >> 18) & 0x7FF);
      receivePackage.deviceId = (uint16_t)(receiveMsg.can_id & 0xFFFF);
      receivePackage.extendpackageFlags = (uint8_t)((receiveMsg.can_id >> 16)& 0x3);
    }
    else
    {
      receivePackage.cmd = (uint16_t)receiveMsg.can_id;
      receivePackage.deviceId = 0;
    }

    receivePackage.length = receiveMsg.can_dlc;

    for (size_t i = 0; i < 8; i++)
      receivePackage.parameters[i] = receiveMsg.data[i];

    executeCommand(&receivePackage);

  }
  else if(state != MCP2515::ERROR_NOMSG)
  {
    Serial.println("Receive Error");
  }

  //Heartbeat
  static uint32_t oldTime =0;
  uint32_t currentTime = millis();
  if (currentTime - oldTime > 10000)
  {
    oldTime = currentTime;
    sendInfoFrame(canCommand::heartBeat);
  }
}

void CanController::sendCommand(canPackage_t* package)
{
  uint32_t id = 0;
  uint16_t cmdId = (uint16_t) (package->cmd & 0x07FF);
  if (package->deviceId == 0)
  {
    id = cmdId;
  }
  else
  {
    id = ((uint32_t)cmdId) << 18;
    id |= package->deviceId | ( ((uint32_t)package->extendpackageFlags) << 16) ;

    id |= CAN_EFF_FLAG;
  }

  sendMsg.can_id = id;
  sendMsg.can_dlc = package->length;
  for (size_t i = 0; i < 8; i++)
  {
    sendMsg.data[i] = package->parameters[i];
  }

  mcp2515.sendMessage(&sendMsg);
}

void CanController::executeCommand(canPackage_t* package)
{

  if(monitorMode)
  {
    Serial.print("(");
    Serial.print(package->cmd, HEX);
    Serial.print(" ");
    Serial.print(package->deviceId, HEX);
    Serial.print(" ");
    Serial.print(package->extendpackageFlags, HEX);
    Serial.print(" ");
    Serial.print(package->length, HEX);
    Serial.print(" ");

    for (size_t i = 0; i< package->length; i++)
    {  // print the data

      Serial.print(package->parameters[i],HEX);
      Serial.print(" ");
    }
    Serial.print(")");
    Serial.println();
  }

  if (package->deviceId != 0
    && package->deviceId != currentSettings.deviceId
    && (package->extendpackageFlags & EXTEND_PACKAGE_FLAG_OWN_ID) == 0)
    return;

  //set
  if (package->cmd == (uint16_t)canCommand::set)
  {
    canSetPackage_u setPackageUnion;
    setPackageUnion.package = *package;
    canSetPackage_t setPackage = setPackageUnion.setPackage;

    if(setPackage.parameter == canParameter::deviceId)
    {
      uint16_t deviceId = (setPackage.parameters[0] << 8);
      deviceId += setPackage.parameters[1];

      currentSettings.deviceId = deviceId;

      Serial.print("New DeviceId: ");
      Serial.println(deviceId,HEX);
    }
    receiveSetMessage(&setPackage);

  }
  else if(package->cmd == (uint16_t)canCommand::saveSettings)
  {
    updateEEPROM();
    boardUpdateEEPROM();
  }
  else if(package->cmd == (uint16_t)canCommand::monitor)
  {
    monitorMode = !monitorMode;
  }

  receiveMessage(package);
}

void CanController::updateEEPROM()
{
  currentSettings.canVersion = CANVERSION;
  currentSettings.boardId = BOARDID;
  currentSettings.boardVersion = BOARDVERSION;
  currentSettings.firmewareVersion = FIRMWAREVERSION;
  dataWrite(0, &currentSettings);
}

void CanController::sendAndExecuteCommand(canCommand cmd)
{
  canPackage_t package;
  package.cmd = (uint16_t)cmd;
  package.extendpackageFlags = EXTEND_PACKAGE_FLAG_OWN_ID;
  package.deviceId = currentSettings.deviceId;
  package.length = 0;

  sendAndExecuteCommand(&package);
}

void CanController::sendAndExecuteCommand(canPackage_t* package)
{
  CanController::sendCommand(package);
  CanController::executeCommand(package);
}
