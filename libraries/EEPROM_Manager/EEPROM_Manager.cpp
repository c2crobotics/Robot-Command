#include "EEPROM_Manager.h"

void initEEPROM() {
  if (EEPROM.read(SIGNATURE_ADDR) != EEPROM_SIGNATURE) {
    EEPROM.write(SIGNATURE_ADDR, EEPROM_SIGNATURE);
    EEPROM.write(NUM_CMDS_ADDR, 0);
  }
}

uint8_t getNumCommands() {
  return EEPROM.read(NUM_CMDS_ADDR);
}

void setNumCommands(uint8_t n) {
  EEPROM.update(NUM_CMDS_ADDR, n);
}

void storeCommand(const String& input) {
  uint8_t numCmds = getNumCommands();
  if (numCmds >= MAX_CMDS) {
    Serial.println(F("Error: EEPROM is full."));
    return;
  }

  int addr = CMDS_START_ADDR + (numCmds * (CMD_LEN + 1));
  char buffer[CMD_LEN + 1];
  input.toCharArray(buffer, CMD_LEN + 1);

  for (int i = 0; i <= CMD_LEN; i++) {
    EEPROM.update(addr + i, buffer[i]);
  }

  setNumCommands(numCmds + 1);
}

String readCommand(uint8_t index) {
  if (index >= getNumCommands()) return String();

  int addr = CMDS_START_ADDR + (index * (CMD_LEN + 1));
  char buffer[CMD_LEN + 1];

  for (int i = 0; i <= CMD_LEN; i++) {
    buffer[i] = EEPROM.read(addr + i);
    if (buffer[i] == '\0') break;
  }
  return String(buffer);
}