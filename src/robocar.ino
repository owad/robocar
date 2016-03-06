#include <Arduino.h>
#include "logger.h"
#include "motor.h"
#include "ultrasound.h"

const int TOGGLE = 8;
const int MIN_DISTANCE = 15;
const int MAX_CURRENT = 90;

int is_on = false;

// pin numbers for: dir, speed, brake, current
int A[4] = {12, 3, 9, A0};
int B[4] = {13, 11, 8, A1};

Motor chassis(A, B, 150);  // left motor, right motor and speed
Ultrasound left_eye(4, 5);
Ultrasound right_eye(6, 7);
Logger dist_log(30);
Logger cur_log(30);

void setup() {
  Serial.begin(9600);
  left_eye.setup();
  right_eye.setup();
  chassis.setup();

  pinMode(TOGGLE, INPUT);
}

void loop() {
  on_off_control();

  int ld = left_eye.get_distance();
  int rd = right_eye.get_distance();
  int avg_dist = (ld+rd) / 2;

  if (avg_dist > 5 && avg_dist < 500) {
    dist_log.push(avg_dist);
  }

  int left_cur = chassis.get_left_current();
  int right_cur = chassis.get_right_current();
  int avg_cur = (left_cur + right_cur) / 2;
  cur_log.push(avg_cur);

  int avg_current = cur_log.get_average();
  int avg_distance = dist_log.get_average();

  if (is_on) {

    if (millis() % 100 == 0) {
      Serial.print("avg: ");
      Serial.print(avg_current);
      Serial.print(", l: ");
      Serial.print(left_cur);
      Serial.print(", r: ");
      Serial.println(right_cur);
    }

    if (avg_current > MAX_CURRENT) {
      if (millis() % 100 == 0) {
        Serial.println("Too high current!");
      }
      if (left_cur > right_cur) {
        chassis.right();
      } else {
        chassis.left();
      }
    } else if (ld < MIN_DISTANCE || rd < MIN_DISTANCE) {
      if (millis() % 100 == 0) {
        Serial.println("Too close from walls!");
      }
      if (rd > ld) {
        chassis.right();
      } else {
        chassis.left();
      }
    } else {
      chassis.go();
    }
  } else {
    chassis.stop();
  }
}

// HELPERS
void on_off_control() {
  if (digitalRead(TOGGLE)) {
    is_on = !is_on;
    delay(500);
  }
}
