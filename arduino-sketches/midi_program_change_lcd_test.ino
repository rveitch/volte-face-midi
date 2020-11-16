#include <MIDI.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

#define MIDI_CHANNEL 1

void setup() {
  lcd.begin(16, 2); // set up the LCD's number of rows and columns:
  resetDisplay();
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    handleProgramChange(MIDI_CHANNEL, i);
    handleControlChange(MIDI_CHANNEL, 0, 0);
    delay (1000);
  }
}

void resetDisplay() {
  resetProgramChangeDisplay();
  resetControlChangeDisplay();
}

void resetProgramChangeDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("PC:       Ch.   ");
}

void resetControlChangeDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("CC:            ");
}

void handleProgramChange(byte channel, byte number) {
  MIDI.sendProgramChange(number, channel);

  resetProgramChangeDisplay();

  // DISPLAY PC Number
  lcd.setCursor(4, 0);
  lcd.print(number, DEC);

  // DISPLAY PC CHANNEL
  lcd.setCursor(14, 0);
  lcd.print(channel, DEC);
}

void handleControlChange(byte channel, byte number, byte value) {
  MIDI.sendControlChange(number, value, channel);

  resetControlChangeDisplay();
  lcd.setCursor(4, 1);
  lcd.print(String(number) + "-" + String(value));
}
