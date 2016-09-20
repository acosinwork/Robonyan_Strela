/*
#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <Servo.h>

#include <PID_v1.h>
*/

#include <SumoBot.h>


int power = 90;

double Setpoint, Input, Output;

double Kp = 1.14, Ki = 0.4, Kd = 0.08;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

SumoBot bot;

void setup() {
  // put your setup code here, to run once:

  bot.begin();
  bot.sensors.attach(P6);
  bot.sensors.attach(P7);

  while (bot.pin.isLow(S2))
  {
    for (int i = 0; i < bot.sensors.count(); ++i)
      bot.sensors.setBlack(i);
  }

  bot.beep(400);

  while (bot.pin.isLow(S4))
  {
    for (int i = 0; i < bot.sensors.count(); ++i)
      bot.sensors.setWhite(i);
  }
  bot.beep(500);

  Input = getLine();
  Setpoint = 0;

  delay(1000);

  //turn the PID on
  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);

}

void loop() {
  // put your main code here, to run repeatedly:

  Input = getLine();
  if (myPID.Compute())
  {
    int uSpeed = Output;
    int brake = (abs(uSpeed) / 2);

    bot.speed(power - uSpeed - brake, power + uSpeed - brake);
  }

}

int getLine()
{
  return (bot.sensors.readPct(0) - bot.sensors.readPct(1));
}




