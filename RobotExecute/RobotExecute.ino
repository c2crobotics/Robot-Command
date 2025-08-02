#include <EEPROM.h>
#include "EEPROM_Manager.h"
#include "Functions.h"
#include "Parser.h"
#include "Queue.h"

// Global queue
Queue queue;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }

  Serial.println("Robot Execution Ready!");

  initEEPROM();
  setupLEDs();

  int numCommands = getNumCommands();
  Serial.print("Loading ");
  Serial.print(numCommands);
  Serial.println(" commands from EEPROM");

  for (int i = 0; i < numCommands; i++) {
    String cmdStr = readCommand(i);
    Command cmd = getCommand(cmdStr);
    
    if (cmd.valid) {
      if (!queue.enqueue(cmd)) {
        Serial.println("Error: Queue is full");
        break;
      }
    } else {
      Serial.print("Error: Skipping invalid command: ");
      Serial.println(cmdStr);
    }
  }
}

void loop() {
  if (!queue.isEmpty()) {
    // processQueue();
  }
  delay(10);
}

void processQueue() {
  while (!queue.isEmpty()) {
    Command cmd = queue.dequeue();
    if (!cmd.valid) {
      Serial.println("Error: Invalid command");
      continue;
    }
    Serial.print("Executing ");
    Serial.println(cmd.name);
    executeCommand(cmd);
    delay(1000);
  }
  Serial.println("Processing is finished.");
}

void executeCommand(Command& cmd) {
    if (!cmd.valid) {
      Serial.println("Error: Invalid command");
      return;
    }
    
    if (cmd.name == "move_forward" && cmd.paramCount == 1) {
      move_forward(cmd.params[0].toInt());
    } 
    else if (cmd.name == "move_backward" && cmd.paramCount == 1) {
      move_backward(cmd.params[0].toInt());
    } 
    else if (cmd.name == "turn_right" && cmd.paramCount == 1) {
      turn_right(cmd.params[0].toInt());
    } 
    else if (cmd.name == "turn_left" && cmd.paramCount == 1) {
      turn_left(cmd.params[0].toInt());
    } 
    else if (cmd.name == "set_speed" && cmd.paramCount == 1) {
      set_speed(cmd.params[0].toInt());
    } 
    else if (cmd.name == "set_led_color" && cmd.paramCount == 2) {
      set_led_color(cmd.params[0], cmd.params[1].toInt());
    } 
    else if (cmd.name == "make_noise" && cmd.paramCount == 0) {
      make_noise();
    } 
    else {
      Serial.print("Invalid command: ");
      Serial.println(cmd.name);
    }
}