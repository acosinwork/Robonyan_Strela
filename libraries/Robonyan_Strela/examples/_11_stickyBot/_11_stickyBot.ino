#include <SumoBot.h>


SumoBot bot;
int maxPower = 90;

int distance = 50;

void setup() {
  // put your setup code here, to run once:

  bot.begin();

  bot.sensors.attach(P7);
  bot.sensors.attach(P8);

  bot.head.ultrasonic.attach(P11, P12);
  bot.head.servo.attach(P3);

  bot.head.ultrasonic.setKF(0.8);

  bot.head.lookAt(0);

  bot.beep();


}

void loop() {


  if (bot.head.getDistance() < distance-distance * 0.1)
    bot.speed(-maxPower);
  else if (bot.head.getDistance() > distance+distance * 0.1)
    bot.speed(maxPower);
  else
    bot.stop();
}


