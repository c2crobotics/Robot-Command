#include "Motor.h"

Motor::Motor(int speedPin, int dir1Pin, int dir2Pin)
    : _speedPin(speedPin), _dir1Pin(dir1Pin), _dir2Pin(dir2Pin), _currentSpeed(100) {}

void Motor::init()
{
    pinMode(_speedPin, OUTPUT);
    pinMode(_dir1Pin, OUTPUT);
    pinMode(_dir2Pin, OUTPUT);
    stop();
}

void Motor::setSpeed(int speed)
{
    _currentSpeed = constrain(speed, 0, 255);
}

void Motor::forward()
{
    digitalWrite(_dir1Pin, HIGH);
    digitalWrite(_dir2Pin, LOW);
    analogWrite(_speedPin, _currentSpeed);
}

void Motor::backward()
{
    digitalWrite(_dir1Pin, LOW);
    digitalWrite(_dir2Pin, HIGH);
    analogWrite(_speedPin, _currentSpeed);
}

void Motor::stop()
{
    digitalWrite(_dir1Pin, LOW);
    digitalWrite(_dir2Pin, LOW);
    analogWrite(_speedPin, 0);
}

void Motor::drive(int milliseconds, bool forwardDirection)
{
    if (forwardDirection)
    {
        forward();
    }
    else
        backward();
    delay(milliseconds);
    stop();
}