


//include libraries

#include <SumoBot.h>  // maybe

//definition of variables
#define DEBUG false//true //show messages between Serial1 and Arduino in serial port

#define KEY_COUNT 9

enum Keys {
  w, a, s, d,
  left, right,
  up, down, space
};

//const int stepsPerRevolution = 500;
//int state = 5;

SumoBot bot;

int maxPower = 80;

byte powerStep = 10;

unsigned long lastTime = 0;

byte timeout = 50;
int startAngle = -8;
int headAngle = startAngle;

byte headAngleStep = 5;

byte process = 0;

//*****
//SETUP
//*****
void setup()
{

  bot.begin();
  bot.head.servo.attach(P3);
  bot.head.setLookUpSector(-50, 50);
  bot.head.lookAt(headAngle);

  //start communication
  Serial.begin(9600);

  Serial1.begin(115200);

  sendData("AT+RST\r\n", 2000, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  sendData("AT+CWJAP=\"Amperka.ru\",\"xxxx\"\r\n", 2000, DEBUG); //connect wi-fi network
  while (!Serial1.find("OK")) { //wait for connection
  }
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //show IP address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //allow multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start web server on port 80

  //Define motor speed

  bot.speed(0, 0);

  lastTime = millis();
}

void loop()
{
  //  bot.head.sectorScaning();


  if (Serial1.available())  //verify incoming data
  {
    if (Serial1.find("+IPD,")) //if there is a message
    {
      String msg;
      Serial1.find("="); //look for the message
      msg = Serial1.readStringUntil(' '); //read whole message

      String keyStr = msg.substring(0, KEY_COUNT);

      lastTime = millis();

      int go = 0;
      int turn = 0;

      if (keyStr.charAt(w) == '1')
        go = 1;
      if (keyStr.charAt(s) == '1')
        go = -1;

      if (keyStr.charAt(up) == '1')
        maxPower = constrain (maxPower + powerStep, 0, 127);

      if (keyStr.charAt(down) == '1')
        maxPower = constrain (maxPower - powerStep, 0, 127);

      if (keyStr.charAt(a) == '1')
        turn = maxPower / 2;
      if (keyStr.charAt(d) == '1')
        turn = - maxPower / 2;

      if (keyStr.charAt(left) == '1')
        headAngle = constrain(headAngle + headAngleStep, -35, 35);

      if (keyStr.charAt(right) == '1')
        headAngle = constrain(headAngle - headAngleStep, -35, 35);

      if (keyStr.charAt(space) == '1')
        headAngle = startAngle;


      bot.head.lookAt(headAngle);

      if (go)
        bot.speed(go * (maxPower - turn), go * (maxPower + turn));
      else
        bot.speed(- turn, turn);

        bot.pin.flashOnlyOneLed(process++ % 4);

        //     String valueStr = msg.substring(4);   //next 3 characters = value
        //     int value = valueStr.toInt();

        if (DEBUG) {
        Serial.println(keyStr);
        }
    }
  }

  if (millis() - lastTime > timeout)
    bot.speed(0, 0);


}

//*******************
//Auxiliary functions
//*******************

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial1.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
