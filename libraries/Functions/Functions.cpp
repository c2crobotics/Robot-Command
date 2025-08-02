#include "Functions.h"

// Setup functions

const int NUM_LEDS = 2;
const int RGB_CHANNELS = 3;

// RGB LED pin definitions
const int LED_PINS[NUM_LEDS][RGB_CHANNELS] = {
    {10, 9, 8}, // LED 1: R, G, B
    {7, 6, 5}   // LED 2: R, G, B
};

// Color mapping structure
struct ColorMap
{
  const char *name;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

const ColorMap COLOR_MAP[] = {
    {"red", 255, 0, 0},
    {"green", 0, 255, 0},
    {"blue", 0, 0, 255},
    {"yellow", 255, 255, 0},
    {"purple", 128, 0, 128},
    {"cyan", 0, 255, 255},
    {"white", 255, 255, 255},
    {"orange", 255, 165, 0},
    {"pink", 255, 192, 203},
    {"lime", 50, 205, 50},
    {"teal", 0, 128, 128},
    {"navy", 0, 0, 128},
    {"off", 0, 0, 0}};

const int COLOR_COUNT = sizeof(COLOR_MAP) / sizeof(ColorMap);

// Initialize LED pins
void setupLEDs()
{
  for (int led = 0; led < NUM_LEDS; led++)
  {
    for (int channel = 0; channel < RGB_CHANNELS; channel++)
    {
      pinMode(LED_PINS[led][channel], OUTPUT);
      analogWrite(LED_PINS[led][channel], 0);
    }
  }
}

// ---------------------------------------------------------- //

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
  // Invalid led index
  if (led < 0 || led >= NUM_LEDS)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      for (int channel = 0; channel < RGB_CHANNELS; channel++)
      {
        analogWrite(LED_PINS[i][channel], 0);
      }
    }
    return;
  }

  // Find color in color map
  bool colorFound = false;
  for (int i = 0; i < COLOR_COUNT; i++)
  {
    if (color.equals(COLOR_MAP[i].name))
    {
      analogWrite(LED_PINS[led][0], COLOR_MAP[i].red);
      analogWrite(LED_PINS[led][1], COLOR_MAP[i].green);
      analogWrite(LED_PINS[led][2], COLOR_MAP[i].blue);

      colorFound = true;
      Serial.print("Set LED ");
      Serial.print(led);
      Serial.print(" to ");
      Serial.println(COLOR_MAP[i].name);
      break;
    }
  }

  // Handle unknown colors
  if (!colorFound)
  {
    // Default to black for unknown colors
    analogWrite(LED_PINS[led][0], 0);
    analogWrite(LED_PINS[led][1], 0);
    analogWrite(LED_PINS[led][2], 0);
  }
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