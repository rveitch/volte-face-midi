# Volte-Face
**Midi Program Change Event Remapper for Arduino Uno R3**

- [Arduino Midi Library](https://github.com/FortySevenEffects/arduino_midi_library)
- [Midi Library Documentation](http://arduinomidilib.fortyseveneffects.com/index.html)
- [Callbacks Documentation](http://playground.arduino.cc/Main/MIDILibraryCallbacks)
- [EEPROM Read](https://www.arduino.cc/en/Tutorial/EEPROMRead)
- [Saving int arrays to EEPROM](http://forum.arduino.cc/index.php?topic=258193.0)

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
  MIDI.setHandleProgramChange(handleProgramChange);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI); 
}

void loop()
{
  // Read messages from the serial port using the main input channel.
  MIDI.read(); //is there incoming MIDI?
}

```

## Signal Chain:

```
OneControl OC-10 Midi Out -> Arduino -> H9 -> Mobius -> Timeline -> BigSky -> CAB
```

## Preset Data Structure

```
Index = Incoming program change # & Array "Row" Index
Ch1-5 = Outgoing program change to send per midi channel (1-5 for five separate devices):
  Ch1 = Eventide H9
  Ch2 = Strymon Mobius
  Ch3 = Strymon Timeline
  Ch4 = Strymon Bigsky
  Ch5 = TwoNotes CAB
```  

```
EEPROM Preset Data Arrays:
Indx Ch1  Ch2  Ch3  Ch4  Ch5
[00] [  ] [  ] [  ] [  ] [  ]
[01] [  ] [  ] [  ] [  ] [  ]
[02] [  ] [  ] [  ] [  ] [  ]
[03] [  ] [  ] [  ] [  ] [  ]
[04] [  ] [  ] [  ] [  ] [  ]
[05] [  ] [  ] [  ] [  ] [  ]
[06] [  ] [  ] [  ] [  ] [  ]
[07] [  ] [  ] [  ] [  ] [  ]
[08] [  ] [  ] [  ] [  ] [  ]
[09] [  ] [  ] [  ] [  ] [  ]
[10] [  ] [  ] [  ] [  ] [  ]
```

## Library Function Examples

```c


/*! Running status enables short messages when sending multiple values
     of the same type and channel.\n
     Set to 0 if you have troubles controlling your hardware.
     //static const bool UseRunningStatus = true;
     */

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
     
```
