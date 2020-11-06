#include <MIDI.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void bootDisplay() {
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
  lcd.print("PC:       Ch.   ");
}

void resetControlChangeDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("CC:            ");
}

void handleControlChange(byte channel, byte number, byte value) {
  resetControlChangeDisplay();
  lcd.setCursor(4, 1);
  lcd.print(String(number) + "-" + String(value));
}

void handleProgramChange(byte channel, byte number) {
  resetProgramChangeDisplay();

  // DISPLAY PC Number
  lcd.setCursor(4, 0);
  lcd.print(number, DEC);

  // DISPLAY PC CHANNEL
  lcd.setCursor(14, 0);
  lcd.print(channel, DEC);
}

void handleError(int8_t err) {
  lcd.setCursor(0, 0);
  lcd.print("ERROR: " + String(err));
  lcd.setCursor(0, 1);
  lcd.print("               ");
}

void setup() {
  lcd.begin(16, 2); // set up the LCD's number of rows and columns:
  bootDisplay();
  
  MIDI.setHandleError(handleError);
  MIDI.setHandleProgramChange(handleProgramChange); // Connect the "handleProgramChange" function to the library for program change callback reception.
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initiate MIDI communications, listen to all channels
  //MIDI.turnThruOff();
}

void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();

  // There is no need to check if there are messages incoming
  // if they are bound to a Callback function.
  // The attached method will be called automatically
  // when the corresponding message has been received.
}
