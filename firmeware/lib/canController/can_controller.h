#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__

#include <stdint.h>
#include "can_package.h"

const uint8_t CANVERSION = 1;

extern const uint8_t BOARDID;
extern const uint8_t BOARDVERSION;
extern const uint8_t FIRMWAREVERSION;

void initCan();
void setupController();
void loopCan();

void updateEEPROM();

void sendCanMessage(canPackage_t*);

void executeCommand(canPackage_t*);

struct __attribute__ ((packed)) canSettings_t
{
  uint8_t canVersion;
  uint8_t boardId;
  uint8_t boardVersion;
  uint8_t firmewareVersion;
  uint16_t deviceId;
};

canSettings_t getSettings();

#endif
