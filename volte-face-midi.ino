#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// --------------------------------------------------------------------------------------------------
// Program Change Callback:
// This function will be automatically called when a program change message (0xC0) has been received.
void handleProgramChange(byte channel, byte number)
{
  // Send Control Change (Bank Select, MSB)
  MIDI.sendControlChange(0, 0, 1); // Needed for Program Changes to work
}
// --------------------------------------------------------------------------------------------------

void setup()
{
  // Connect the "handleProgramChange" function to the library for program change callback reception.
  MIDI.handleProgramChange(handleProgramChange);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI); 
}

void loop()
{
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
