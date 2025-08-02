#include "Parser.h"

// Define the colors array
const String COLORS[] = {"red", "green", "blue", "yellow", "purple", "cyan", "white", "orange", "pink", "lime", "teal", "navy", "off"};

String trim(const String &str)
{
  int start = 0;
  int end = str.length() - 1;
  while (start <= end && str.charAt(start) == ' ')
    start++;
  while (end >= start && str.charAt(end) == ' ')
    end--;
  return str.substring(start, end + 1);
}

Command getCommand(const String &input)
{
  Command cmd;
  int openParen = input.indexOf('(');
  int closeParen = input.indexOf(')');
  
  // Find parentheses
  cmd.hasParentheses = (openParen != -1 && closeParen != -1 && closeParen > openParen);
  
  // Handle commands without parentheses
  if (!cmd.hasParentheses)
  {
    cmd.name = trim(input);
    cmd.valid = true;
    return cmd;
  }
  
  // Handle command with parentheses
  cmd.name = trim(input.substring(0, openParen));
  String paramStr = input.substring(openParen + 1, closeParen);
  paramStr = trim(paramStr);
  
  // Parse parameters
  if (paramStr.length() > 0)
  {
    int startIdx = 0;
    int commaPos;
    do
    {
      commaPos = paramStr.indexOf(',', startIdx);
      String token = (commaPos == -1) ? paramStr.substring(startIdx) : paramStr.substring(startIdx, commaPos);
      token = trim(token);
      if (token.length() > 0 && cmd.paramCount < 5)
      {
        cmd.params[cmd.paramCount++] = token;
      }
      startIdx = commaPos + 1;
    } while (commaPos != -1 && cmd.paramCount < 5);
  }
  
  cmd.valid = true;
  return cmd;
}

bool isValidInt(const String &str, int minVal, int maxVal)
{
  if (str.length() == 0)
    return false;
  
  for (unsigned int i = 0; i < str.length(); i++)
  {
    char c = str.charAt(i);
    if (!isdigit(c) && !(i == 0 && c == '-'))
    {
      return false;
    }
  }
  
  int value = str.toInt();
  return value >= minVal && value <= maxVal;
}

bool isValidColor(const String &str)
{
  for (String color : COLORS) {
    if (color == str) {
      return true;
    }
  }
  return false;
}