#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int speedPin, int dir1Pin, int dir2Pin); 
    void init();
    void setSpeed(int speed);
    void forward();
    void backward();
    void stop();
    void drive(int milliseconds, bool forwardDirection);

private:
    int _speedPin;
    int _dir1Pin;
    int _dir2Pin;
    int _currentSpeed;
};

#endif