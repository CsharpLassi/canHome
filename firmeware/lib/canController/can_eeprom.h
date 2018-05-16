#ifndef __CAN_EEPROM_H__
#define __CAN_EEPROM_H__

#include <stdint.h>
#include <EEPROM.h>

const uint16_t eepromSize = 1024;
const uint8_t pageSize = 64;

const uint8_t pageCount = eepromSize/pageSize;

template<typename T>
union byteDataType_t
{
  T dataType;
  uint8_t datas[sizeof(T)];
};

template<typename T>
void dataWrite(uint8_t pos,T* data)
{
  if(pos > pageCount -1)
    return;

  static_assert(sizeof(T) <= pageSize, "Datasize is too big" );

  byteDataType_t<T> dataType;
  dataType.dataType = *data;

  uint16_t startPos = pos * pageSize;
  for (uint8_t i = 0; i < sizeof(T); i++)
    EEPROM.write(startPos + i, dataType.datas[i]);
}

template<typename T>
T dataRead(uint8_t pos)
{
  if(pos > pageCount -1)
    return;

  static_assert(sizeof(T) <= pageSize, "Datasize is too big");

  byteDataType_t<T> dataType;

  uint16_t startPos = pos * pageSize;
  for (uint8_t i = 0; i < sizeof(T); i++)
    dataType.datas[i] = EEPROM.read(startPos+i);

  return dataType.dataType;
}



#endif
