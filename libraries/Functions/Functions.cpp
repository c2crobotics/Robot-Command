#include "Functions.h"

void move_forward(int seconds)
{
  Serial.print(F("Robot moving forward for "));
  Serial.print(seconds);
  Serial.println(F(" seconds"));
}

void move_backward(int seconds)
{
  Serial.print(F("Robot moving backward for "));
  Serial.print(seconds);
  Serial.println(F(" seconds"));
}

void turn_right(int degrees)
{
  Serial.print(F("Robot turning "));
  Serial.print(degrees);
  Serial.println(F(" degrees right"));
}

void turn_left(int degrees)
{
  Serial.print(F("Robot turning "));
  Serial.print(degrees);
  Serial.println(F(" degrees left"));
}

void set_speed(int speed)
{
  Serial.print(F("Setting robot speed to: "));
  Serial.println(speed);
}

void set_led_color(String color, int led)
{
  Serial.print(F("Setting LED #"));
  Serial.print(led);
  Serial.print(F(" to color: "));
  Serial.println(color);
}

void make_noise()
{
  Serial.println(F("Robot made a noise!"));
}

void print_list()
{
  uint8_t numCmds = getNumCommands();
  Serial.print(F("Stored commands: "));
  Serial.println(numCmds);
  for (int i = 0; i < numCmds; i++)
  {
    Serial.print(i + 1);
    Serial.print(F(": "));
    Serial.println(readCommand(i));
  }
}

void clear_list()
{
  setNumCommands(0);
  Serial.println(F("List cleared"));
}

void printHelp()
{
  Serial.println(F("Available commands:"));
  Serial.println(F("- move_forward(x): Move robot forward for x seconds, [0-100]"));
  Serial.println(F("- move_backward(x): Move robot backward for x seconds, [0-100]"));
  Serial.println(F("- turn_right(x): Turn robot right x degrees, [0-360]"));
  Serial.println(F("- turn_left(x): Turn robot left x degrees, [0-360]"));
  Serial.println(F("- set_speed(x): Set robot speed to x, [-100-100]"));
  Serial.println(F("- set_led_color(color, led): Change an LED's color, [0-32]"));
  Serial.println(F("- make_noise(): Make a noise"));
  Serial.println(F("- print_list(): Print the list of commands for the robot"));
  Serial.println(F("- clear_list(): Clear the list of commands for the robot"));
  Serial.println(F("- help(): Show this message"));
}