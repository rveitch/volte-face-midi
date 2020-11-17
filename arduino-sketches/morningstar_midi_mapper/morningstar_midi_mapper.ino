#include <math.h>
#include <MIDI.h>
#include <LiquidCrystal.h>


// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

#define MIDI_THRU_DISABLED true
#define MIDI_CHANNEL_LISTEN MIDI_CHANNEL_OMNI // listen to all channels
#define MIDI_CHANNEL_OUT 1

#define MIDI_OFFSET 0
#define CONTROL_CHANGE_VALUE 1
#define PRESETS_PER_BANK 12
#define PRESET_MIN 10

void setup() {
  bootDisplay();

  MIDI.setHandleError(handleError);
  MIDI.setHandleProgramChange(handleProgramChange);
  // MIDI.setHandleControlChange(handleControlChange);

  //if (MIDI_THRU_DISABLED == true) {
    //MIDI.turnThruOff();
  //}

  MIDI.begin(MIDI_CHANNEL_LISTEN); // Initiate MIDI communications

  MIDI.turnThruOff();
  // MIDI.setThruFilterMode(DifferentChannel); // All the messages but the ones on the Input Channel will be sent back.

  resetMorningstarMidi();
  displayReadyState();
}

void loop() {
  MIDI.read();
}

void bootDisplay() {
  // Set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  
  // Home message
  lcd.setCursor(0, 0);
  lcd.print(" Veitch Digital ");
  lcd.setCursor(0, 1);
  lcd.print("  MIDI Devices  ");

  //delay (3000);
}

void displayReadyState() {
  lcd.setCursor(0, 0);
  lcd.print(" AWAITING  MIDI ");
  lcd.setCursor(0, 1);
  lcd.print("               ");
}

void resetDisplay() {
  resetProgramChangeDisplay();
  resetControlChangeDisplay();
}

void resetProgramChangeDisplay() {
  lcd.setCursor(0, 0);
  lcd.print(" IN: PC    Ch   ");
  lcd.setCursor(0, 1);
  lcd.print("OUT: PC    CC   ");
}

void resetControlChangeDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("OUT: PC    CC   ");
}

void resetMorningstarMidi() {
  MIDI.sendProgramChange(0, MIDI_CHANNEL_OUT);
  MIDI.sendControlChange(10, CONTROL_CHANGE_VALUE, MIDI_CHANNEL_OUT);
}

void handleControlChange(byte channel, byte number, byte value) {
  resetControlChangeDisplay();
  lcd.setCursor(4, 1);
  lcd.print(String(number) + "-" + String(value));
}

void handleProgramChange(byte channel, byte incomingProgramChange) {
  int bankPC = (floor(incomingProgramChange / PRESETS_PER_BANK) + MIDI_OFFSET);
  int presetCC = ((incomingProgramChange - (PRESETS_PER_BANK * (bankPC - MIDI_OFFSET))) + PRESET_MIN);

  MIDI.sendProgramChange(bankPC, channel);
  MIDI.sendControlChange(presetCC, CONTROL_CHANGE_VALUE, channel);

  // Reset Display
  resetProgramChangeDisplay();

  // DISPLAY the PC IN Number
  lcd.setCursor(7,0);
  lcd.print(incomingProgramChange, DEC);

  // DISPLAY the CHANNEL
  lcd.setCursor(15,0);
  lcd.print(channel, DEC);

  // DISPLAY the PC OUT Number
  lcd.setCursor(7,1);
  lcd.print(bankPC, DEC);

  // DISPLAY the CC OUT Number
  lcd.setCursor(14,1);
  lcd.print(presetCC, DEC);
}

void handleError(int8_t err) {
  lcd.setCursor(0, 0);
  lcd.print("ERROR: " + String(err));
  lcd.setCursor(0, 1);
  lcd.print("               ");
}
