#include "Queue.h"

Queue::~Queue() {
  clear();
}

bool Queue::enqueue(const Command& cmd) {
  if (count >= maxSize) {
    return false;
  }

  Node* newNode = new Node{cmd, nullptr};
  if (tail == nullptr) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }

  count++;
  return true;
}

Command Queue::dequeue() {
  if (head == nullptr) { 
    Command emptyCmd;
    emptyCmd.valid = false;
    return emptyCmd;
  }

  Node* temp = head;
  Command cmd = temp->cmd;
  head = head->next;
  
  if (head == nullptr) {
    tail = nullptr;
  }
  
  delete temp;
  count--;
  return cmd;
}

bool Queue::isEmpty() const {
  return count == 0;
}

int Queue::size() const {
  return count;
}

void Queue::clear() {
  while (!isEmpty()) {
    dequeue();
  }
}