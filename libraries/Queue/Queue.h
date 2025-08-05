#ifndef QUEUE_H
#define QUEUE_H

#include "Parser.h"
#include "EEPROM_Manager.h"
#include <Arduino.h>

class Queue {
private:
  struct Node {
    Command cmd;
    Node* next;
  };
  
  Node* head = nullptr;
  Node* tail = nullptr;
  int count = 0;
  const int maxSize = MAX_CMDS;

public:
  ~Queue();
  bool enqueue(const Command& cmd);
  Command dequeue();
  bool isEmpty() const;
  int size() const;
  void clear();
};

#endif