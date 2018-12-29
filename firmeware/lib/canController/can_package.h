#ifndef __CAN_PACKAGE_H__
#define __CAN_PACKAGE_H__


#include <stdint.h>

const uint8_t EXTEND_PACKAGE_FLAG_OWN_ID = 0x01;

enum class canCommand: uint16_t
{
  None = 0,

  boot = 1,
  heartBeat = 2,
  saveSettings = 3,
  monitor = 4,

  set = 16,
  get = 17,
  on = 18,
  off = 19,

  TriggerOn = 32,
  TriggerOff = 33,
};

struct canStringCommand
{
  const char* command;
  canCommand commandId;
};

enum class canParameter : uint8_t
{
  deviceId = 1,
  setMode = 16,

  color = 128,
  backgroundColor = 129,
  foregroundColor = 130,
  delay = 131,
};

struct __attribute__ ((packed)) canPackage_t
{
  uint8_t extendpackageFlags;
  uint16_t deviceId;
  uint16_t cmd;
  uint8_t length;
  uint8_t parameters[8];
};

struct __attribute__ ((packed)) canSetPackage_t
{
  uint8_t extendpackageFlags;
  uint16_t deviceId;
  uint16_t cmd;
  uint8_t length;
  canParameter parameter;
  uint8_t parameters[7];
};

union canSetPackage_u
{
  canPackage_t package;
  canSetPackage_t setPackage;
};

#endif
