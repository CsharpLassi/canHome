#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__

#include <stdint.h>

const uint8_t CANVERSION = 1;

extern const uint8_t BOARDID;
extern const uint8_t BOARDVERSION;
extern const uint8_t FIRMWAREVERSION;

void initCan();

#endif
