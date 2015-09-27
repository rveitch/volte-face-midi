# volte-face-midi-pc-event-remapper
Volte-Face - Midi Program Change Event Remapper for Arduino Uno R3


# Initial Example:
- - - 

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// ----------------------------------------------------------------------------------------------
// This function will be automatically called when a PC is received.
// There is no need to check for incoming messages if they are bound to a Callback function.
// This method will be called automatically when the corresponding message has been received.

void handleProgramChange(byte channel, byte number)
{
  // Do this whenever a Program Change (0xC0) is recieved:
  MIDI.sendControlChange(0, 0, 1); //Needed for Program Changes to work. (Because CC Bank MSB?) (Control Function: Bank Select, USED AS: MSB)
}
// ----------------------------------------------------------------------------------------------

void setup()
{
  MIDI.handleProgramChange(handleProgramChange); // Connect the "handleNoteOn" FUNCTION to the library so it is called upon reception of a ProgramChange.
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initiate MIDI communications, listen to all channels
}

void loop()
{
  // Read messages from the serial port using the main input channel.
    // RETURNS: True if a valid message has been stored in the structure, false if not.
    // A valid message is a message that matches the input channel.
    // If the Thru is enabled and the message matches the filter, it is sent back on the MIDI output.
    // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read(); //is there incoming MIDI?
}
