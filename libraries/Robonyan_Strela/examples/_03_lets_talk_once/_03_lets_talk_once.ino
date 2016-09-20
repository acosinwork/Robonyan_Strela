#include <SumoBot.h>  // maybe

SumoBot bot;

void setup() {
  bot.begin();

  bot.pin.turnOn(L1);
}

void loop ()
{
  delay(1000);
  bot.voice.play();
  bot.done();
}
