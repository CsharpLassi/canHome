#include "can_controller.h"
#include "board.h"

#include <EEPROM.h>

#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(10);
struct can_frame receiveMsg;
struct can_frame sendMsg;

uint16_t deviceId = 0;

void sendInfoFrame(canCommand);

void initCan()
{
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS,MCP_16MHZ);
  mcp2515.setLoopbackMode();
  //mcp2515.setNormalMode();

  sendInfoFrame(canCommand::boot);
}

void sendInfoFrame(canCommand cmd)
{
  if (deviceId == 0)
    return;

  canPackage_t infoPackage;
  infoPackage.cmd = (uint16_t)cmd;
  infoPackage.deviceId = deviceId;
  infoPackage.length = 6;

  infoPackage.parameters[0] = deviceId >> 8;
  infoPackage.parameters[1] = deviceId & 0xFF;
  infoPackage.parameters[2] = CANVERSION;
  infoPackage.parameters[3] = BOARDID;
  infoPackage.parameters[4] = BOARDVERSION;
  infoPackage.parameters[5] = FIRMWAREVERSION;

  sendCanMessage(&infoPackage);
}

void loopCan()
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
    }
    else
    {
      receivePackage.cmd = (uint16_t)receiveMsg.can_id;
      receivePackage.deviceId = 0;
    }

    receivePackage.length = receiveMsg.can_dlc;

    for (size_t i = 0; i < 8; i++)
      receivePackage.parameters[i] = receiveMsg.data[i];

    Serial.print("(");
    Serial.print(receivePackage.cmd, HEX);
    Serial.print(" ");
    Serial.print(receivePackage.deviceId, HEX);
    Serial.print(" ");
    Serial.print(receivePackage.length, HEX);
    Serial.print(" ");

    for (size_t i = 0; i<receivePackage.length; i++)
    {  // print the data

      Serial.print(receivePackage.parameters[i],HEX);
      Serial.print(" ");
    }
    Serial.print(")");
    Serial.println();
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

void sendCanMessage(canPackage_t* package)
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
    id |= package->deviceId;

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

void executeCommand(canPackage_t* package)
{
  if (package->deviceId != 0 && package->deviceId != deviceId)
    return;

  //set
  if (package->cmd == (uint16_t)canCommand::set)
  {
    canSetPackage_u setPackageUnion;
    setPackageUnion.package = *package;
    canSetPackage_t setPackage = setPackageUnion.setPackage;

    if(setPackage.parameter == canParameter::deviceId)
    {
      deviceId = (setPackage.parameters[0] << 8);
      deviceId += setPackage.parameters[1];

      Serial.print("New DeviceId: ");
      Serial.println(deviceId,HEX);
    }
    receiveSetMessage(&setPackage);

  }
  else if(package->cmd == (uint16_t)canCommand::saveSettings)
  {

  }
  receiveMessage(package);
}
