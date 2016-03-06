#include <Arduino.h>
#include "logger.h"

Logger::Logger(int log_size) {
  size = log_size;
  data = new int[log_size];
}

void Logger::push(int value) {
      for (int i=0; i<size-1; i++) {
        data[i] = data[i+ 1];
      }
      data[size-1] = value;
    }

void Logger::clear() {
  for (int i=0; i<size; i++) {
    data[i] = 0;
  }
}

void Logger::print() {
  for (int i=0; i<size; i++) {
    Serial.print(data[i]);
    Serial.print(", ");
  }
  Serial.println("");;
}

int Logger::get_average() {
  int sum = 0;
  for (int i=0; i<size; i++) {
    sum += data[i];
  }
  return sum / size;
}
