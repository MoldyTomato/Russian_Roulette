
#define PIN_A 12
#define PIN_B 11
const int8_t KNOBDIR[] = {
  0, -1, 1, 0,
  1, 0, 0, -1,
  -1, 0, 0, 1,
  0, 1, -1, 0
};
volatile int8_t _oldState;
volatile long _position;        // Internal position (4 times _positionExt)
volatile long _positionExt;     // External position
volatile long _positionExtPrev; // External position (used only for direction checking)
unsigned long _positionExtTime;     // The time the last position change was detected.
unsigned long _positionExtTimePrev; // The time the previous position change was detected.
// ----- Constructor -----
void RotaryEncoder_init() {

  // Setup the input pins and turn on pullup resistor
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);

  // when not started in motion, the current state of the encoder should be 3
  int sig1 = digitalRead(PIN_A);
  int sig2 = digitalRead(PIN_B);
  _oldState = sig1 | (sig2 << 1);

  // start with position 0;
  _position = 0;
  _positionExt = 0;
  _positionExtPrev = 0;
};

// simple retrieve of the direction the knob was rotated last time. 0 = No rotation, 1 = Clockwise, -1 = Counter Clockwise
int8_t Encoder_getDirection() {
  int sig1 = digitalRead(PIN_A);
  int sig2 = digitalRead(PIN_B);
  int8_t thisState = sig1 | (sig2 << 1);

  if (_oldState != thisState) {
    _position += KNOBDIR[thisState | (_oldState << 2)];
    _oldState = thisState;
    if ((thisState == 0) || (thisState == 3)) {
      // The hardware has 2 steps with a latch on the input state 0 and 3
      _positionExt = _position >> 1;
      _positionExtTimePrev = _positionExtTime;
      _positionExtTime = millis();
    }
  }
  int8_t ret = 0;
  if (_positionExtPrev > _positionExt) {
    ret = -1;
    _positionExtPrev = _positionExt;
  } else if (_positionExtPrev < _positionExt) {
    ret = 1;
    _positionExtPrev = _positionExt;
  } else {
    ret = 0;
    _positionExtPrev = _positionExt;
  }
  return ret;
};
