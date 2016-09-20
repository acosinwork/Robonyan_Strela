  #include "Buttons.h"

  #define BUTTON_TIMEOUT_CHECK 10
  #define BUTTON_COUNT         4

bool Buttons::check()
{
  getState();
  uint8_t stateChanges = _lastFilteredState ^ _currentFiltredState;
  if (stateChanges)
  {
          // get all changes from 0 to 1
    _newPress = stateChanges & (~_lastFilteredState);
          //get all changes from 1 to 0
    _newRelease = stateChanges & (~_currentFiltredState);

    for (int i = 0; i < BUTTON_COUNT; ++i) {

      uint8_t mask = 1<<i;

      if (_pressCalbackAttached && (_newPress & mask)) {
        _pressedButton = i + S1;
        pressCallback();
      }

      if (_releaseCalbackAttached && (_newRelease & mask)) {

        _releasedButton = i + S1;
        releaseCallback();
      }
    }
  }
  return (_newPress || _newRelease);
}

void Buttons::onPress(void (*callback)())
{
  pressCallback = callback;
  _pressCalbackAttached = true;
}

void Buttons::onRelease(void (*callback)())
{
  releaseCallback = callback;
  _releaseCalbackAttached = true;
}

uint8_t Buttons::getState()
{
  if (_checkFQ.timeout(BUTTON_TIMEOUT_CHECK)) {

    uint8_t measureNum = ++_buttonCheckCounter % BUTTONS_MEASURE_COUNT;
    _lastButtonState[measureNum] = buttonsState();

    uint8_t pressed, released;

    pressed = released = _lastButtonState[measureNum];

    for (uint8_t i = 0; i < BUTTONS_MEASURE_COUNT; ++i)
    {
      pressed &= _lastButtonState[i];
      released |= _lastButtonState[i];
    }
    _lastFilteredState = _currentFiltredState;
    _currentFiltredState = pressed & released;
  }
  return _currentFiltredState;
}


uint8_t Buttons::getPressedButton() 
{
  return _pressedButton;
}

uint8_t Buttons::getReleasedButton()
{
  return _releasedButton;
}

uint8_t Buttons::waitForPress()
{
  while (!check() || !_newPress) {
    ;;
  }
  return getPressedButton();
}