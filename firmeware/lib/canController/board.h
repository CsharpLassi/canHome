#ifndef __BOARD_H__
#define __BOARD_H__

#include "can_package.h"

void boardLoop();
void boardSetup();
void receiveSetMessage(canSetPackage_t*);
void receiveMessage(canPackage_t*);


#endif
