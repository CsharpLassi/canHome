#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__

#include <stdint.h>
#include "can_package.h"

const uint8_t CANVERSION = 1;

extern const uint8_t BOARDID;
extern const uint8_t BOARDVERSION;
extern const uint8_t FIRMWAREVERSION;

struct __attribute__ ((packed)) canSettings_t
{
  uint8_t canVersion;
  uint8_t boardId;
  uint8_t boardVersion;
  uint8_t firmewareVersion;
  uint16_t deviceId;
};

class CanController
{
  private:
    static void sendInfoFrame(canCommand);
  public:
    static void initCan();
    static void setupController();
    static void loopCan();

    static void updateEEPROM();

    static void sendAndExecuteCommand(canCommand);
    static void sendAndExecuteCommand(canPackage_t*);

    static void executeCommand(canPackage_t*);
    static void sendCommand(canPackage_t*);

    static canSettings_t getSettings();
};
#endif
