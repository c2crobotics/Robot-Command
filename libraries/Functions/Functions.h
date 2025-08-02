#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "EEPROM_Manager.h"

// Command implementations
void move_forward(int seconds);
void move_backward(int seconds);
void turn_right(int degrees);
void turn_left(int degrees);
void set_speed(int speed);
void set_led_color(String color, int led);
void make_noise();
void print_list();
void clear_list();
void printHelp();

// Setup functions
void setupLEDs();

#endif