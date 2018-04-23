#include <parse.h>

#include <Arduino.h>

hsvwColor_t parseColor(String* cmd,uint16_t* index)
{
  uint8_t rgb[3];

  uint16_t rIndex = *index;

  if((*cmd)[ rIndex+ 1 ] == '#')
  {
    rIndex += 1;
    rgb[0] = strtoul(cmd->substring(rIndex+1,rIndex+3).c_str(), NULL, 16);
    rgb[1] = strtoul(cmd->substring(rIndex+3,rIndex+5).c_str(), NULL, 16);
    rgb[2] = strtoul(cmd->substring(rIndex+5,rIndex +7).c_str(), NULL, 16);
    *index = rIndex +7;
  }
  else
  {
    for (uint8_t i = 0; i < 3; i++)
    {
      uint16_t spaceIndexOne =  cmd->indexOf(' ', *index);
      uint16_t spaceIndexTwo =  cmd->indexOf(' ', *index+1);

      rgb[i] = strtoul(cmd->substring(spaceIndexOne,spaceIndexTwo).c_str(), NULL, 10);

      *index = spaceIndexTwo;
    }
  }



  return convertToHSV(rgb[0],rgb[1],rgb[2]);
}
