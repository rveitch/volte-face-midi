#include <MIDI.h>

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

#define MIDI_CHANNEL 1
#define BANK_MSB_LSB_ENABLED false

void setup() {
  MIDI.begin();
}

void loop() {
  for (int i = 0; i < 3; i++) {

    if (BANK_MSB_LSB_ENABLED) {
      MIDI.sendControlChange(0, 0, MIDI_CHANNEL); // Needed for Strymon?
    }
    
    MIDI.sendProgramChange(i, MIDI_CHANNEL);
    
    delay (1000);
  }
}
