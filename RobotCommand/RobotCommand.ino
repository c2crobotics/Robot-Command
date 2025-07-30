#include <EEPROM.h>
#include "EEPROM_Manager.h"
#include "Parser.h"
#include "Functions.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  Serial.println("Serial Ready!");
  initEEPROM();
  printHelp();
}

void loop() {
  processCommands();
  delay(10);
}

void processCommands() {
  if (!Serial.available()) return;

  String input = Serial.readStringUntil('\n');
  input.trim();
  if (input.length() <= 0) return;

  Command cmd = getCommand(input);
  cmd.name.toLowerCase();

  String error = "";
  bool shouldStore = false;

  // Validate command structure first
  if (!cmd.hasParentheses) {
    error = "Missing parentheses in command: " + input;
  }
  // Handle specific commands
  else if (cmd.name == "move_forward") {
    if (cmd.paramCount != 1) error = "move_forward requires 1 parameter";
    else if (!isValidInt(cmd.params[0], 0, 100)) error = "Invalid value (0-100)";
    else {
      move_forward(cmd.params[0].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "move_backward") {
    if (cmd.paramCount != 1) error = "move_backward requires 1 parameter";
    else if (!isValidInt(cmd.params[0], 0, 100)) error = "Invalid value (0-100)";
    else {
      move_backward(cmd.params[0].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "turn_right") {
    if (cmd.paramCount != 1) error = "turn_right requires 1 parameter";
    else if (!isValidInt(cmd.params[0], 0, 360)) error = "Invalid value (0-360)";
    else {
      turn_right(cmd.params[0].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "turn_left") {
    if (cmd.paramCount != 1) error = "turn_left requires 1 parameter";
    else if (!isValidInt(cmd.params[0], 0, 360)) error = "Invalid value (0-360)";
    else {
      turn_left(cmd.params[0].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "set_speed") {
    if (cmd.paramCount != 1) error = "set_speed requires 1 parameter";
    else if (!isValidInt(cmd.params[0], -100, 100)) error = "Invalid value (-100 to 100)";
    else {
      set_speed(cmd.params[0].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "set_led_color") {
    if (cmd.paramCount != 2) error = "set_led_color requires 2 parameters";
    else if (!isValidInt(cmd.params[1], 0, 32)) error = "Invalid LED index (0-32)";
    else {
      set_led_color(cmd.params[0], cmd.params[1].toInt());
      shouldStore = true;
    }
  } else if (cmd.name == "make_noise") {
    if (cmd.paramCount != 0) error = "make_noise takes no parameters";
    else {
      make_noise();
      shouldStore = true;
    }
  } else if (cmd.name == "print_list") {
    if (cmd.paramCount != 0) error = "print_list takes no parameters";
    else print_list();
  } else if (cmd.name == "clear_list") {
    if (cmd.paramCount != 0) error = "clear_list takes no parameters";
    else clear_list();
  } else if (cmd.name == "help") {
    if (cmd.paramCount != 0) error = "help takes no parameters";
    else printHelp();
  } else {
    error = "Unknown command: " + cmd.name;
  }

  // Handle errors
  if (error.length() > 0) {
    Serial.println("Error: " + error);
  }

  // Store valid commands
  if (shouldStore) {
    storeCommand(input);
  }
}