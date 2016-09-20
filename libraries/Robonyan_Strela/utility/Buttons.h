#include "Wire.h"
#include "Strela.h"
#include <inttypes.h>
#include "Amp_ino.h"

#define BUTTONS_MEASURE_COUNT 3

class Buttons{
public:

  bool check();
  uint8_t getState();

  uint8_t waitForPress();

  uint8_t getPressedButton();
  uint8_t getReleasedButton();
  
  void onPress(void (*callback)());
  void onRelease(void (*callback)());

  void (*pressCallback)();
  void (*releaseCallback)();

private:

  TimeOut _checkFQ;
  uint8_t _buttonCheckCounter;
  uint8_t _lastButtonState[BUTTONS_MEASURE_COUNT];
  uint8_t _currentFiltredState;
  uint8_t _lastFilteredState;
  uint8_t _newPress;
  uint8_t _newRelease;

  bool _pressCalbackAttached = false;
  bool _releaseCalbackAttached = false;

  uint8_t _pressedButton;
  uint8_t _releasedButton;
  


};
