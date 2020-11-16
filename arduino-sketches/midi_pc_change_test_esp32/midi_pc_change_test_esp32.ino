#include <MIDI.h>

int ledPin = 13;

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    MIDI.sendProgramChange(i, 1);
    MIDI.sendControlChange(0, 0, 1);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
