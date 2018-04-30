#include <parse.h>

#include <Arduino.h>

const uint8_t MAXSIZE = 10;
const uint8_t DATASIZE = 8;

canPackage_t parsePackage(char* cmd,uint8_t* index)
{
  canPackage_t packageData;

  uint16_t datas[DATASIZE];

  for (size_t a = 0; a < DATASIZE; a++)
    datas[a] = 0x00;

  register uint8_t i = *index;
  register uint8_t j = 0;


  register char c;

  register uint8_t size = MAXSIZE;
  register uint8_t base = 10;

  register uint8_t k = 0;
  char str[MAXSIZE+1];

  while ((c = cmd[i++]) != 0 && j < DATASIZE)
  {
    if(c == ' ')
    {
      if(k > 0)
      {
        str[k] = '\0';
        datas[j++] = strtoul(str, NULL, base);
      }

      k = 0;
      size = MAXSIZE;
      base = 10;
      continue;
    }

    if (c == '#' || c == 'x')
    {
      base = 16;
      size = 2;
      continue;
    }

    str[k++] = c;
    k%=size;
    if( k == 0)
    {
      str[size] = '\0';
      datas[j++] = strtoul(str, NULL, base);
    }


  }

  if(k > 0 && j < DATASIZE)
  {
    str[k] = '\0';
    datas[j++] = strtoul(str, NULL, base);
  }


  *index = i;

  j = 0;
  packageData.deviceId = datas[j++];
  //packageData.cmd = (canCommand)datas[j++];

  for (k = 0; k < 7; k++)
  {
    packageData.parameters[k] =(uint8_t)datas[j++];
  }

  return packageData;
}
