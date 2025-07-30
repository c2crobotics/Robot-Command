#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>

struct Command {
  String name;
  bool valid = false;
  int paramCount = 0;
  bool hasParentheses = false;
  String params[5];  // max 5 params
};

String trim(const String& str);
Command getCommand(const String& input);
bool isValidInt(const String& str, int minVal, int maxVal);

#endif