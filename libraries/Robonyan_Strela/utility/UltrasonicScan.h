
#ifndef _ULTRASONIC_SCAN_H_
#define _ULTRASONIC_SCAN_H_

#include <Arduino.h>
#include "Amp_ino.h"
#include "Servo.h"

#include <stddef.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <Wprogram.h>
#endif

class Ultrasonic
{
	public:
		/*
		 *@param tp:trigger pin
		 *@param ep:echo pin
		 */
		Ultrasonic();

		void attach(int tp,int ep);
		
		long timing();//return Ultrasonic sensor send and receive total time
		/*
		 *@param microsec:Ultrasonic sensor send and receive total time
	 	 *@param metric:the value decide return value is Centimeters or inches
	 	 *@return calculate distance
		 */ 
		float CalcDistance(long microsec,int metric);
		/*
		 *@param value:modify divisor value
		 *@param metric:judge set value is Centimeters divisor value or inches divisor value
		 */
		void SetDivisor(float value,int metric);
		static const int CM = 1;
		static const int IN = 0;
	protected:
		int _trigPin;//Trigger Pin
		int _EchoPin;//Echo Pin
		float _cmDivisor;//centimeter divisor parameter
		float _inDivisor;//Inches divisor parameter
		
};
 
class UltrasonicTimeout : public Ultrasonic
{
public:
	UltrasonicTimeout(long timeout);

	UltrasonicTimeout();

	void setTimeout(long timeout);

	long timing();

private:

	long _timeout;
};


class UltrasonicFiltered : public UltrasonicTimeout
{
public:

	UltrasonicFiltered() : UltrasonicTimeout(){}

    void setKF(float k_filter);
	float getRawDistance();
	float getDistance();
	void setSilenceTime(int time);

private:

	uint16_t _silenceTime = 25;
	bool _newDistance;
	float _kFilt = 0.35;
	float _oldDistance = 0;
	bool _firstMeasure = true;
	TimeOut _betweenMeasurements;
};

class UltrasonicScaner
{
public:
	
	UltrasonicScaner();

	void lookAt(int angle);

	float getDistance();
	int getAngle();
	

	void setLookUpSector(int fromAngle, int toAngle);

	void setServoStep(uint8_t step);


	bool sectorScaning();

	Servo servo;
	UltrasonicFiltered ultrasonic;
	
private:
    int _sectorStart;
    int _sectorEnd;

	enum ServoState {
		clockwise,
		counterclockwise
	} _servoState;

	uint8_t _servoStep;

    int _servoTimeout;
	int _currentAngle;
	


//	bool _clockWiseRotation = true;
//	bool _seek = false;


	TimeOut sweep;

};


#endif