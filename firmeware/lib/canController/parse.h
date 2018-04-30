#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdint.h>
#include "can_package.h"

canPackage_t parsePackage(char*,uint8_t*);

#endif
