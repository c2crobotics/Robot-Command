#include "Functions.h"
#include "Motor.h"

// Setup functions

// Setup Motors
const int DUMMY_PIN = -1;
Motor leftMotor(DUMMY_PIN, DUMMY_PIN, DUMMY_PIN);
Motor rightMotor(DUMMY_PIN, DUMMY_PIN, DUMMY_PIN);

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

// Initialize Motor pins
void setupMotors()
{
  leftMotor.init();
  rightMotor.init();
}

// Initialize LED pins
void setupLEDs()
{
  for (int led = 0; led < NUM_LEDS; led++)
  {
    for (int channel = 0; channel < RGB_CHANNELS; channel++)
    {
      pinMode(LED_PINS[led][channel], OUTPUT);
      digitalWrite(LED_PINS[led][channel], 0);
    }
  }
}

// ---------------------------------------------------------- //

void move_forward(int seconds)
{
  Serial.print(F("Robot moving forward for "));
  Serial.print(seconds);
  Serial.println(F(" seconds"));

  leftMotor.forward();
  rightMotor.forward();
  set_led_color("green", 0);
  set_led_color("green", 1);
  
  delay(seconds * 100);
  
  leftMotor.stop();
  rightMotor.stop();
  
  set_led_color("off", 1);
  set_led_color("off", 0);
  // LED Test
}

void move_backward(int seconds)
{
  Serial.print(F("Robot moving backward for "));
  Serial.print(seconds);
  Serial.println(F(" seconds"));

  leftMotor.backward();
  rightMotor.backward();
  set_led_color("red", 0);
  set_led_color("red", 1);
  
  delay(seconds * 100);
  
  leftMotor.stop();
  rightMotor.stop();

  set_led_color("off", 0);
  set_led_color("off", 1);

  // LED Test
}

void turn_right(int degrees)
{
  Serial.print(F("Robot turning "));
  Serial.print(degrees);
  Serial.println(F(" degrees right"));

  leftMotor.forward();
  rightMotor.backward();

  set_led_color("red", 0);
  set_led_color("green", 1);
  
  delay(degrees * 10);
  
  leftMotor.stop();
  rightMotor.stop();

  set_led_color("off", 0);
  set_led_color("off", 1);
}

void turn_left(int degrees)
{
  Serial.print(F("Robot turning "));
  Serial.print(degrees);
  Serial.println(F(" degrees left"));

  leftMotor.backward();
  rightMotor.forward();

  set_led_color("green", 0);
  set_led_color("red", 1);
  
  delay(degrees * 10);

  leftMotor.stop();
  rightMotor.stop();

  set_led_color("off", 0);
  set_led_color("off", 1);
}

void set_speed(int speed)
{
  Serial.print(F("Setting robot speed to: "));
  Serial.println(speed);

  leftMotor.setSpeed(speed);
  rightMotor.setSpeed(speed);

  set_led_color("pink", 0);
  set_led_color("pink", 1);
  delay(2000);
  set_led_color("off", 0);
  set_led_color("off", 1);

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
        digitalWrite(LED_PINS[i][channel], 0);
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
      digitalWrite(LED_PINS[led][0], COLOR_MAP[i].red);
      digitalWrite(LED_PINS[led][1], COLOR_MAP[i].green);
      digitalWrite(LED_PINS[led][2], COLOR_MAP[i].blue);

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
    digitalWrite(LED_PINS[led][0], 0);
    digitalWrite(LED_PINS[led][1], 0);
    digitalWrite(LED_PINS[led][2], 0);
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
  Serial.println(F("- set_speed(x): Set robot speed to x, [0-255]"));
  Serial.println(F("- set_led_color(color, led): Change an LED's color, [0-4]"));
  Serial.println(F("- make_noise(): Make a noise"));
  Serial.println(F("- print_list(): Print the list of commands for the robot"));
  Serial.println(F("- clear_list(): Clear the list of commands for the robot"));
  Serial.println(F("- help(): Show this message"));
}