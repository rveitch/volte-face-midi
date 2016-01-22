#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// --------------------------------------------------------------------------------------------------
// Program Change Callback:
// This function will be automatically called when a program change message (0xC0) has been received.
void handleProgramChange(byte channel, byte number)
{
  // Send Control Change (Bank Select, MSB)
  MIDI.sendControlChange(0, 0, 1); // Needed for Program Changes to work
  MIDI.sendProgramChange(69, 1); // Change the voice (add+1pg for eventide)
}
// --------------------------------------------------------------------------------------------------

void setup()
{
  // Connect the "handleProgramChange" function to the library for program change callback reception.
  MIDI.setHandleProgramChange(handleProgramChange);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI); 
}

void loop()
{
  MIDI.read(); //is there incoming MIDI?
  //{
    //for (int pgm = 1; pgm < 99; pgm++) // Sets up for the voice loop
    //{
      //MIDI.sendProgramChange(pgm, 1); // Change the voice
      //MIDI.sendControlChange(0, 0, 1); // Needed for Program Changes to work
      //delay(1000); // 1 second delay
    //}
  //}
}
