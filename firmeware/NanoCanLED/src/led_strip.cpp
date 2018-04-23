#include <led_strip.h>
#include <animation.h>

#include <stdint.h>
#include <Arduino.h>

static animation* currentAnimation = NULL;
static settings currentSettings;
static bool interrupt = false;


void initLedStrip()
{
  pinMode(pinNum, OUTPUT);
  digitalWrite(pinNum, HIGH);

  //Todo:Init
  strip.begin();
}

void ledStripUpdateTask(void)
{
  if(currentAnimation == NULL)
  {
    return;
  }
  currentAnimation->start();
  currentAnimation->drawNext(&strip, &currentSettings, &interrupt);
  currentAnimation->end();
  currentAnimation = NULL;
  interrupt = false;
}

void setAnimation(animation* newAnimation)
{
  if (currentAnimation != NULL)
  {
    interrupt = true;
    while (interrupt)
      delay(10);
  }

  currentAnimation = newAnimation;
}

void setOn()
{
  static onAnimation animation;
  animation.ledDelay = 10;


  setAnimation(&animation);
}

void setOff()
{
  static offAnimation animation;

  setAnimation(&animation);
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
