#include <led_strip.h>
#include <animation.h>

#include <stdint.h>
#include <Arduino.h>

animation* currentAnimation = NULL;
settings currentSettings;

bool run = false;
defaultAnimation defaultAnimation;

void initLedStrip()
{
  pinMode(pinNum, OUTPUT);
  digitalWrite(pinNum, HIGH);

  //Todo:Init
  strip.begin();
}

void ledStripUpdateTask(void)
{
  if(!run)
    return;

  if(currentAnimation == NULL)
    currentAnimation = &defaultAnimation;

  currentAnimation->start();
  if(currentAnimation->drawNext(&strip, &currentSettings))
  {
    currentAnimation->end();
    currentAnimation = NULL;
  }
}

void setAnimation(animation* newAnimation)
{
  currentAnimation = newAnimation;
}

void setOn()
{
  static onAnimation animation;
  animation.ledDelay = 10;


  setAnimation(&animation);

  run = true;
}

void setOff()
{
  static offAnimation animation;

  setAnimation(&animation);
  ledStripUpdateTask();

  run = false;
}

void startBarAnimation()
{
  static barAnimation animation;

  setAnimation(&animation);
}

void startBarAnimation(rgbwColor_t color)
{
  static barAnimation animation;
  animation.setForegroundColor(createPWMColor(color));

  setAnimation(&animation);
}

void setBackgroundColor(pixelColor_t color)
{
  currentSettings.backgroundColor = color;
}

void setForegroundColor(pixelColor_t color)
{
  currentSettings.foregroundColor = color;
}

void setBackgroundColor(hsvwColor_t color)
{
  currentSettings.backgroundColor = createPWMColor(color);
}

void setForegroundColor(hsvwColor_t color)
{
  currentSettings.foregroundColor = createPWMColor(color);
}
