#include <inttypes.h>
#include <Arduino.h>
#include "Wire.h"
#include "Strela.h"
#include "Notes.h"

class Melody {
public:

	void play()
	{
		for (int i = 0; i < sizeof(_win)/sizeof(_win[0]); ++i) {
			if (_win[i][0] > 0)
				tone(BUZZER, _win[i][0], _win[i][1]);
			delay(_win[i][1]);
		}

	};

private:
	uint16_t _win[7][2] = {
		{NOTE_G3, 100},
		{NOTE_C4, 100},
		{NOTE_G4, 100},
		{NOTE_C5, 100},
		{0, 150},
		{NOTE_G4, 100},
		{NOTE_C5, 200},
		

	};



};