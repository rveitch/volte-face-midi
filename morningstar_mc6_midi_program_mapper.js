const MIDI_OFFSET = 1;
const BANK_MIN = 1;
const BANK_MAX = 30;
const PRESETS_PER_BANK = 12; // CC# 10-21, Presets A-L
const PRESET_MIN = 10; // Control Change # - Preset A
const PRESET_MAX = 21;// Control Change # - Preset L
const CONTROL_CHANGE_VALUE = 1; // Control Change Value - (1 = On Press)

function getBank(incomingProgramChange) {
  return Math.floor(incomingProgramChange / PRESETS_PER_BANK) + MIDI_OFFSET;
}

function getPreset(incomingProgramChange, bank) {
  const minPresetForBank = PRESETS_PER_BANK * (bank - MIDI_OFFSET);
  return (incomingProgramChange - minPresetForBank) + PRESET_MIN;
}

function mapIncomingEvent(incomingProgramChange) {
  const bank = getBank(incomingProgramChange);
  const present = getPreset(incomingProgramChange, bank);
  return {
    pc: bank,
    cc: present,
    ccv: CONTROL_CHANGE_VALUE,
  };
}

// mapIncomingEvent(24); // Uncomment to run example.