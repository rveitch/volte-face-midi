# Volte-Face
**Midi Program Change Event Remapper for Arduino Uno R3**

- [Arduino Midi Library](https://github.com/FortySevenEffects/arduino_midi_library)
- [Midi Library Documentation](http://arduinomidilib.fortyseveneffects.com/index.html)

## Initial Example:

```c

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
  // Read messages from the serial port using the main input channel.
  MIDI.read(); //is there incoming MIDI?
}

```

## Library Functions

```c


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
     
```
