
/*! Running status enables short messages when sending multiple values
     of the same type and channel.\n
     Set to 0 if you have troubles controlling your hardware.
     //static const bool UseRunningStatus = true;
     */

/*!
MIDI.begin();   // Launch MIDI with default options
MIDI.read(); //is there incoming MIDI?
getType(): returns the type of the message (valid types are decribed above)
getChannel(): returns the channel of the message (1-16)
getData1(): returns the first data byte (0-127)
getData2(): returns the 2nd data byte (0-127)
check(): returns true if the message is valid, else false.
MIDI.turnThruOn();
MIDI.turnThruOff();
MIDI.setInputChannel(1); // input channel is set to 1
UseRunningStatus = true
  //Running status enables short messages when sending multiple values of the same type and channel.
  //Set to 0 if you have troubles controlling your hardware.
MIDI.getData1();
getType();
getTypeFromStatusByte();
send();
setHandleProgramChange();
setThruFilterMode();
disconnectCallbackFromType();
     */
// -----------------------------------------------------------------------------
     
#include <MIDI.h>
//Create an instance of the library with default name, serial port and settings
//MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

int ledPin = 13;                 // LED connected to digital pin 13
byte P = 0;  //program or patch number

// -----------------------------------------------------------------------------
// This function will be automatically called when a PC is received.
// It must be a void-returning function with the correct parameters,
void handleProgramChange(byte channel, byte number)
{
    // Do whatever you want when a pc is pressed.
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    MIDI.sendControlChange(0, 0, 1);
}
     
void setup() {
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.begin();
}

void loop() {
  MIDI.read(); //is there incoming MIDI?
  //{
    //for (int pgm = 1; pgm < 99; pgm++) // Sets up for the voice loop
    //{
      //digitalWrite(ledPin, HIGH);   // sets the LED on
      //MIDI.sendProgramChange(pgm, 1); // Change the voice
      //MIDI.sendNoteOff(42,0,1);   // Stop the note
      //MIDI.sendControlChange(0, 0, 1);
      //delay(1000);      // 1 second delay
      //digitalWrite(ledPin, LOW);    // sets the LED off
      //delay(1000);                  // waits for a second
    //}
  //}
}
