# Volte-Face
**Midi Program Change Event Remapper for Arduino Uno R3**

- [Arduino Midi Library](https://github.com/FortySevenEffects/arduino_midi_library)
- [Midi Library Documentation](http://arduinomidilib.fortyseveneffects.com/index.html)

## Initial Example:

```c

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

// ----------------------------------------------------------------------------------------------
// Program Change Callback:
// This function will be automatically called when a PC is received.
// There is no need to check for incoming messages if they are bound to a Callback function.
// This method will be called automatically when the corresponding message has been received.

void handleProgramChange(byte channel, byte number)
{
  // Do this whenever a Program Change (0xC0) is received:
    // Send Control Change - Bank Select MSB
  MIDI.sendControlChange(0, 0, 1); //Needed for Program Changes to work?
}
// ----------------------------------------------------------------------------------------------

void setup()
{
  // Connect the "handleNoteOn" FUNCTION to the library so it is called upon reception of a ProgramChange.
  MIDI.handleProgramChange(handleProgramChange);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI); 
}

void loop()
{
  // Read messages from the serial port using the main input channel.
  MIDI.read(); //is there incoming MIDI?
}

```
