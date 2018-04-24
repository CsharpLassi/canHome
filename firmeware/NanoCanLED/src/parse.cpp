#include <parse.h>

#include <Arduino.h>


hsvwColor_t parseColor(char* cmd,uint8_t* index)
{
  uint8_t rgbw[4];

  register uint8_t i = *index;
  register uint8_t j = 0;
  register uint8_t k = 0;

  register char c;

  register uint8_t size = 3;
  uint8_t base = 10;
  char str[4];


  while ((c = cmd[i++]) != 0)
  {
    if(c == ' ')
      continue;

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
      rgbw[j++] = strtoul(str, NULL, base);
    }

  }

  *index = i;

  /*

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

*/

  return convertToHSV(rgbw[0],rgbw[1],rgbw[2]);
}
