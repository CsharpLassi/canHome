#ifndef __CAN_PACKAGE_H__
#define __CAN_PACKAGE_H__


#include <stdint.h>

enum class canCommand: uint16_t
{
  None = 0,

  boot = 1,
  heartBeat = 2,
  saveSettings = 3,

  set = 16,
  get = 17,
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
  uint16_t deviceId;
  uint16_t cmd;
  uint8_t length;
  uint8_t parameters[8];
};

struct __attribute__ ((packed)) canSetPackage_t
{
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
