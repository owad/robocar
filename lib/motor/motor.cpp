#include <Arduino.h>
#include "motor.h"

// pin numbers for: dir, speed, brake, current
Motor::Motor(int* left, int* right, int motor_speed) {
  left_wheel = left;
  right_wheel = right;
  speed = motor_speed;
}

void Motor::setup() {
  for(int i=0; i<4; i++) {
    pinMode(left_wheel[i], OUTPUT);
    pinMode(right_wheel[i], OUTPUT);
  }
}

void Motor::set_direction(const int* motor, int dir) {  // motor can be either forward or backward
  digitalWrite(motor[0], !(dir == 1));
}

void Motor::set_speed(const int* motor, int m_speed) {  // speed is percentage of max PWM
  if (m_speed < 0) {
    Motor::set_direction(motor, 0); // backward
  } else {
    Motor::set_direction(motor, 1);  // forward
  }
  analogWrite(motor[1], float(abs(m_speed) * 255) * 0.01);
}

void Motor::stop() {
  Motor::set_speed(left_wheel, 0);
  Motor::set_speed(right_wheel, 0);
}

void Motor::go() {
  Motor::set_speed(left_wheel, speed);
  Motor::set_speed(right_wheel, speed);
}

void Motor::forward() {
  Motor::set_speed(left_wheel, speed);
  Motor::set_speed(right_wheel, speed);
}

void Motor::backward() {
  Motor::set_speed(left_wheel, -1 * speed);
  Motor::set_speed(right_wheel, -1 * speed);
}

void Motor::left() {
  Motor::set_speed(left_wheel, speed);
  Motor::set_speed(right_wheel, -1 * speed);
}

void Motor::right() {
  Motor::set_speed(left_wheel, -1 * speed);
  Motor::set_speed(right_wheel, speed);
}

void Motor::breaks(bool val) {
  digitalWrite(left_wheel[2], val);
  digitalWrite(right_wheel[2], val);
}

int Motor::get_left_current() {
  return analogRead(right_wheel[3]);
}

int Motor::get_right_current() {
  return analogRead(left_wheel[3]);
}
