/*
#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
*/

#include <SumoBot.h>  // maybe

/*
//#include <Amp_ino.h>
#include <Servo.h>
*/
#define MOVE_TIME  500
#define STEP_COUNT 8

#define FORWARD    0
#define BACK       1
#define LEFT       2
#define RIGHT      3

SumoBot bot;

int steps[STEP_COUNT];

int currentStep = 0;

void setup() {

  bot.begin();

  bot.pin.turnOn(L1);

  bot.buttons.onPress(fillRoad);

  while (currentStep < STEP_COUNT)
  {
    bot.buttons.check();
  }

  for (int i = 0; i < 3; ++i)
  {
    delay(1000);
    bot.beep(1000 + i * 50);

  }
}

void loop ()
{
  while (currentStep)
  {
    --currentStep;

    switch (steps[currentStep])
    {
      case FORWARD:
        bot.speed(100, 100);
        break;
      case BACK:
        bot.speed(-100, -100);
        break;
      case LEFT:
        bot.speed(-100, 100);
        break;
      case RIGHT:
        bot.speed(100, -100);
    }

    delay(MOVE_TIME);
  }

  bot.stop();
  delay(1000);

  bot.voice.play();
  bot.done();

}

void fillRoad()
{
  bot.beep();

  int pressedButton = bot.buttons.getPressedButton();

  switch (pressedButton)
  {
    case S1:
      steps[currentStep] = FORWARD;
      break;
    case S2:
      steps[currentStep] = BACK;
      break;
    case S3:
      steps[currentStep] = LEFT;
      break;
    case S4:
      steps[currentStep] = RIGHT;
      break;
  }
  ++currentStep;
}
