
int steps[8];

void setup() {
	for (int i = 0; i < 8; ++i)
		steps[i] = waitForButtonPress();
}

void loop() {
	for (int i = 0; i < 8; ++i) {
		if (steps[i] == BUTTON_S1)
			motorWrite(255, 255);
		else if (steps[i] == BUTTON_S2)
			motorWrite(255, 0);
		else if (steps[i] == 3)
			motorWrite(0, 255);
		else
			motorWrite(-128, -128);

		delay(1000);
	}
}