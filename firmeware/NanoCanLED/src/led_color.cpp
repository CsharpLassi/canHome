#include <led_color.h>

#include <WString.h>


using namespace std;

const float piOver6 = 0.5235987755982988;
const float pi = 3.141592653589793;

pixelColor_t pixelFromRGB(uint8_t,uint8_t,uint8_t);

hsvwColor_t convertToHSV(uint8_t r,uint8_t g,uint8_t b)
{
  rgbwColor_t color = {.r = r, .g = g, .b = b};

  return convertToHSV(color);
}

hsvwColor_t convertToHSV(rgbwColor_t color)
{
  hsvwColor_t newColor;
  newColor.w = color.w;

  float r = color.r /(float)255;
  float g = color.g /(float)255;
  float b = color.b /(float)255;

  float max = r;
  float min = r;
  uint8_t maxColor = 0;

  if (g > max)
  {
    maxColor = 1;
    max = g;
  }
  if(g < min)
  {
    min = g;
  }

  if (b > max)
  {
    maxColor = 2;
    max = b;
  }
  if(b < min)
  {
    min = b;
  }

  float delta = max -min;

  if (delta == 0)
    newColor.h = 0;
  else if(maxColor == 0 )
    newColor.h = piOver6 * (0+(g-b)/(delta));
  else if(maxColor == 1 )
    newColor.h = piOver6 * (2+(b-r)/(delta));
  else if(maxColor == 2 )
    newColor.h = piOver6 * (4+(r-g)/(delta));

  if(newColor.h < 0)
    newColor.h += pi;

  if (max == 0)
    newColor.s = 0;
  else
    newColor.s = delta/max;

  newColor.v = max;

  return newColor;
}

pixelColor_t createPWMColor(rgbwColor_t color)
{
  hsvwColor_t hsvValue = convertToHSV(color);

  return createPWMColor(hsvValue);
}

pixelColor_t createPWMColor(hsvwColor_t color)
{
  float h = color.h;
  float s = color.s;
  float v = color.v;

  if(v > (maxBrightness/(float)255))
    v =  maxBrightness/(float)255;

  //v = 0.01;

  uint8_t hi = (uint16_t) (h / piOver6);

  float f = (h / piOver6) - hi;

  float p = v *(1-s);
  float q = v *(1-s*f);
  float t = v *(1-s*(1-f));

  float r;
  float g;
  float b;


  if(hi == 0 || hi == 6)
  {
    r = v;
    g = t;
    b = p;
  }
  else if (hi==1)
  {
    r = q;
    g = v;
    b = p;
  }
  else if (hi==2)
  {
    r = p;
    g = v;
    b = t;
  }
  else if (hi==3)
  {
    r = p;
    g = q;
    b = v;
  }
  else if (hi==4)
  {
    r = t;
    g = p;
    b = v;
  }
  else if (hi==5)
  {
    r = v;
    g = p;
    b = q;
  }

  uint8_t br = (uint8_t)(r*255);
  uint8_t bg = (uint8_t)(g*255);
  uint8_t bb = (uint8_t)(b*255);

  return pixelFromRGB(br,bg,bb);
}

pixelColor_t pixelFromRGB(uint8_t r,uint8_t g,uint8_t b)
{
  pixelColor_t color;
  color.r = r;
  color.g = g;
  color.b = b;

  return color;
}
