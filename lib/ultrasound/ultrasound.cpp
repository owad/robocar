#include <Arduino.h>
#include "ultrasound.h"

Ultrasound::Ultrasound(int trig, int echo) {
  trig_pin = trig;
  echo_pin = echo;
}

void Ultrasound::setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

int Ultrasound::get_distance() {
  digitalWrite(trig_pin, LOW);
  delay(1);
  digitalWrite(trig_pin, HIGH);
  delay(5);
  digitalWrite(trig_pin, LOW);
  long duration = pulseIn(echo_pin, HIGH);
  return (duration/2) / 34.03;
}
