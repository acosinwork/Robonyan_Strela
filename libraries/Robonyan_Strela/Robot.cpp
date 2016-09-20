#include "Arduino.h"

#include "Robot.h"
#include <Strela.h>

#include "utility/MotorCalibration.h"

#define DEFAULT_ACCEL 50


Robot::Robot()
{
 
	/*TODO*/

//	Robot::acceleration(DEFAULT_ACCEL);
}

void Robot::begin()
{
	strelaInitialize();

	MotorCalibration(_motorMaxSpeed);

	if (_motorMaxSpeed[1] != 0) 
		motorsDiffMultiplier = (float)_motorMaxSpeed[0] / _motorMaxSpeed[1];

}

void Robot::done()
{
	stop();
	
	while (true)
		;;
}

void Robot::stop()
{
	speed(0);
}

void Robot::writeMotorsSpeed(int motorLeft, int motorRight)
{
	motorLeft = (float)motorLeft * motorsDiffMultiplier;

	drive(motorLeft, motorRight);
}

void Robot::speed(int motorLeft, int motorRight)
{
//	motorLeft = constrain(motorLeft, 0, 100);
//	motorRight = constrain(motorRight, 0, 100);
    writeMotorsSpeed(motorLeft, motorRight);	
}

void Robot::speed(int spd)
{
	speed(spd, spd);
}

void Robot::beep(int freq, int toneLength)
{
	tone(BUZZER, freq, toneLength);
}


/*

void acceleration(uint8_t accel)
{
	_acceleration = accel;
}

*/