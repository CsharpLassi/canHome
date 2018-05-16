#ifndef __PORT_SETTING_H__
#define __PORT_SETTING_H__

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

#include <led_color.h>


enum class porttypes_t : uint8_t
{
  Off = 0,
  input = 1,
  input_pullup=2,
  adc_8 = 3,
  adc_10 = 4,
  output = 5,
  led_strip = 6,
};

struct __attribute__ ((packed)) portsettings_t
{
  porttypes_t type;
  bool onOffState;

  uint16_t ledNumbers;

  pixelColor_t backgroundColor;
  pixelColor_t foregroundColor;
  uint16_t delay;
};

#endif
