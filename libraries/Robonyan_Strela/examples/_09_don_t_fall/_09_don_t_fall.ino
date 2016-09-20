#include <SumoBot.h>  // maybe

SumoBot bot;

void setup() {
  bot.begin();

  bot.pin.turnOn(L1);

  bot.sensors.attach(P7);

  //бот должен уже стоять на столе, чтобы инит нормально прошел
  bot.sensors.setWhite(0);
}

void loop ()
{
  while (bot.sensors.readPct(0) < 50)
    bot.speed(40, 40);

// боремся с иннерцией
  while (bot.sensors.readPct(0) >= 50)
  {
    bot.speed(-255,-255);
    delay(100);
  }

  bot.stop();

  delay(1000);
  bot.voice.play();
  bot.done();
}
