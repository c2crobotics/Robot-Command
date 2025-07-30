#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

// EEPROM configuration
#define EEPROM_SIGNATURE 0xAA
#define SIGNATURE_ADDR 0
#define NUM_CMDS_ADDR 1
#define CMDS_START_ADDR 2
#define MAX_CMDS 20
#define CMD_LEN 50

void initEEPROM();
uint8_t getNumCommands();
void setNumCommands(uint8_t n);
void storeCommand(const String& input);
String readCommand(uint8_t index);

#endif