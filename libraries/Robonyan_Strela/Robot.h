#ifndef ROBOT_H
#define ROBOT_H

#include <inttypes.h>
#include "utility/Strela.h"
#include "utility/Melodies.h"



class Robot {

	public:
		Robot();

		void speed(int motorLeft, int motorRight);

		void speed(int spd);

/*
		void forvard(int speed);

		void backvard(int speed);

		void stop();

		void acceleration(int8_t accel);
*/
//		virtual void run();

//	protected:

		void begin();
		void done();
		void stop();

		void beep(int freq = 1000, int toneLength = 50);

		

    private:

    	int _motorMaxSpeed[2] = {0, 0};

    	float motorsDiffMultiplier;

    	void writeMotorsSpeed(int motorLeft, int motorRight);

/*
    	uint8_t _acceleration;

    	uint8_t _currentSpeed;
*/

};

#endif