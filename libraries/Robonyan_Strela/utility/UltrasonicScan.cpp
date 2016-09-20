#include "UltrasonicScan.h"

//#define ULTRASONIC_MEASURE_TIMEOUT 25UL

#define MIN_ANGLE -90
#define MAX_ANGLE 90

#define SG_90_MOVE_MULT    130/60 
#define DEFAULT_SERVO_STEP 5
 

Ultrasonic::Ultrasonic()
{
	_cmDivisor = 27.6233;
	_inDivisor = 70.1633;
}

void Ultrasonic::attach(int tp,int ep)
{
	pinMode(tp,OUTPUT);
	pinMode(ep,INPUT);
	_trigPin = tp;
	_EchoPin = ep;
}

long Ultrasonic::timing()
{
	digitalWrite(_trigPin,LOW);
	delayMicroseconds(2);
	digitalWrite(_trigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigPin,LOW);
	return pulseIn(_EchoPin,HIGH); 
}

float Ultrasonic::CalcDistance(long microsec,int metric)
{
	if(metric)//centimeter divisor
		return microsec / _cmDivisor / 2.0;
	else //inches divisor
		return microsec /_inDivisor / 2.0;
}

void Ultrasonic::SetDivisor(float value,int metric)
{
	if(metric)//centimeter divisor
		_cmDivisor = value;
	else
		_inDivisor = value;
}

///////////////
UltrasonicTimeout::UltrasonicTimeout(long timeout) : Ultrasonic()
{
	setTimeout(timeout);
}

UltrasonicTimeout::UltrasonicTimeout() : Ultrasonic()
{
	setTimeout(15000); // ~2.5 m
}

	void UltrasonicTimeout::setTimeout(long timeout)
{
	_timeout = timeout;
}


long UltrasonicTimeout::timing()
{
	digitalWrite(_trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(_trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigPin, LOW);
	return pulseIn(_EchoPin, HIGH, _timeout); 
}

///////////////

void UltrasonicFiltered::setKF(float k_filter)
{
	_firstMeasure = true;
	_kFilt = k_filter;
}

float UltrasonicFiltered::getRawDistance()
{
	if (long timingIsCorrect = timing())
		return CalcDistance(timingIsCorrect, CM);
	else
		return _oldDistance;
}

float UltrasonicFiltered::getDistance()
{

	if (_firstMeasure) {
		_oldDistance = getRawDistance();
		_firstMeasure = false;
	}
	else if (_betweenMeasurements.timeout(_silenceTime))
	{
		_oldDistance = (1.0 - _kFilt) * _oldDistance + _kFilt * getRawDistance();
	}

	return _oldDistance;
}

void UltrasonicFiltered::setSilenceTime(int time)
{
	_silenceTime = time;
}

////////////////

    UltrasonicScaner::UltrasonicScaner()
    {
    	setServoStep(DEFAULT_SERVO_STEP); 
  
    	_sectorStart = MIN_ANGLE;
    	_sectorEnd = MAX_ANGLE;
    }


	void UltrasonicScaner::lookAt(int angle)
	{
		constrain(angle, MIN_ANGLE, MAX_ANGLE);
		_currentAngle = angle;
		servo.write(angle + 90);
	}

	float UltrasonicScaner::getDistance()
	{
		return ultrasonic.getDistance();
	}

	int UltrasonicScaner::getAngle()
	{
		return _currentAngle;
	}

	void UltrasonicScaner::setServoStep(uint8_t step)
	{
		_servoTimeout = SG_90_MOVE_MULT * step;
		_servoStep = step;

	}



	void UltrasonicScaner::setLookUpSector(int fromAngle, int toAngle)
	{
		if (fromAngle < toAngle)
		{
			_sectorStart = fromAngle;
			_sectorEnd = toAngle;
		}
		else
		{
			_sectorStart = toAngle;
			_sectorEnd = fromAngle;
		}

		int rightArcAngle = abs(_currentAngle - _sectorStart);
		int leftArcAngle = abs(_currentAngle - _sectorEnd);

		if (rightArcAngle < leftArcAngle)
			_servoState = clockwise;
		else
			_servoState = counterclockwise;
		
		/*
		if (_currentAngle <= _sectorStart)
			_servoState = counterclockwise;
		else if (_currentAngle >= _sectorEnd)
			_servoState = clockwise;

//deleteit
		_servoState = clockwise;
		*/

	}

bool UltrasonicScaner::sectorScaning()
{		
	bool result = false;





	if (sweep.timeout(_servoTimeout)) 
	{			
		switch (_servoState)
		{
			case clockwise:
			{
				if (_currentAngle > _sectorStart)
					lookAt(_currentAngle - _servoStep);
				else {
					_servoState = counterclockwise;
				    result = true;
				}
			}
			break;

			case counterclockwise:
			{
				if (_currentAngle < _sectorEnd)
					lookAt(_currentAngle + _servoStep);
				else {
					_servoState = clockwise;
					result = true;
				}
			}
			break;
		}
	}
	return result;
}





