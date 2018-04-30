#ifndef __CAN_PACKAGE_H__
#define __CAN_PACKAGE_H__


#include <stdint.h>

enum class canCommand: uint8_t
{
  None = 0,

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
  canCommand cmd;
  uint8_t parameters[7];
};

struct __attribute__ ((packed)) canSetPackage_t
{
  uint16_t deviceId;
  canCommand cmd;
  canParameter parameter;
  uint8_t parameters[6];
};

union canSetPackage_u
{
  canPackage_t package;
  canSetPackage_t setPackage;
};

#endif
