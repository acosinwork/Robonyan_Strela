#include <SumoBot.h>

enum State {
  findGarbage,
  clearIt,
  done
} state;


SumoBot bot;
int maxPower = 80;
int minDistanceAngle, minDistance;

int white;

float radToDeg = PI / 180;

void setup() {
  // put your setup code here, to run once:

  bot.begin();

  bot.sensors.attach(P7);
  bot.sensors.attach(P8);

  while (!uDigitalRead(S2))
  {
    for (int i = 0; i < bot.sensors.count(); ++i)
      bot.sensors.setBlack(i);
  }

  tone(BUZZER, 400, 100);

  while (!uDigitalRead(S4))
  {
    for (int i = 0; i < bot.sensors.count(); ++i)
      bot.sensors.setWhite(i);
  }
  tone(BUZZER, 500, 100);


  bot.head.ultrasonic.attach(P11, P12);
  bot.head.servo.attach(P3);

  bot.head.ultrasonic.setKF(0.8);
  
  //bot.head.ultrasonic.setSilenceTime(15);

  bot.head.setLookUpSector(-15, 15);

  bot.head.lookAt(0);
  minDistance = 1000;//bot.head.getDistance();


  Serial.begin(9600);
}

void loop() {
  
//  Serial.println(bot.head.getDistance());
  

  // put your main code here, to run repeatedly:
  
  bot.head.sectorScaning();

  //maxPower = map(analogRead(P9), 0, 1023, 20, 120);

  showCase(state);

  switch (state)
  {
    case findGarbage:

      if ((bot.head.getDistance() < 60))
      {
        tone(BUZZER, 1000, 20);

        bot.speed(0, 0);

        state = clearIt;
      } else {
        bot.speed(-maxPower * 0.8, maxPower * 0.8);
      }

      break;

    case clearIt:

      if ((bot.sensors.readPct(0) > 40) || (bot.sensors.readPct(1) > 40)) {
        bot.speed(0, 0);
        state = done;
      } else if ((bot.head.getDistance() < 60))
        bot.speed(maxPower, maxPower);
      else
        state = findGarbage;

      break;

    case done:


      if ((bot.sensors.readPct(0) > 60) || (bot.sensors.readPct(1) > 60)) {

        bot.speed(-maxPower * (0.8 + bot.sensors.readPct(0) / 100), -maxPower * (0.8 + bot.sensors.readPct(1) / 100));

      } else if (bot.head.getDistance() < 30)
        bot.speed(-maxPower, 0);
      else
        state = findGarbage;


      break;
  }
  
}



void showCase(int curr)
{
  switch (curr)
  {
    case findGarbage:

      uDigitalWrite(L1, HIGH);
      uDigitalWrite(L2, LOW);
      uDigitalWrite(L3, LOW);


      break;

    case clearIt:


      uDigitalWrite(L1, LOW);
      uDigitalWrite(L2, HIGH);
      uDigitalWrite(L3, LOW);

      break;

    case done:


      uDigitalWrite(L1, LOW);
      uDigitalWrite(L2, LOW);
      uDigitalWrite(L3, HIGH);

      break;
  }
}
