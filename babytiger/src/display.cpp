// Controls an 16x16 WS2812B LED matrix display, via an Arduono Nano through I2C.
#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <Wire.h>
#include "display.h"


bool display_switch = true;
uint8_t display_data[128];

void set_pixel(int8_t x, int8_t y, enum COLOR c) {
  if (x < 0 || x > 15 || y < 0 || y > 15) return; // Discard offscreen draws

  uint8_t index;
  if (x % 2) {
    index = (15 - x) * 16 + 15 - y;
  } else {
    index = (15 - x) * 16 + y;
  }

  if (index % 2) {
    display_data[index / 2] = (uint8_t) c | (display_data[index / 2] & 0xf0);
  } else {
    display_data[index / 2] = (uint8_t) c << 4 | (display_data[index / 2] & 0x0f);
  }
}

void clear_pixels() {
  memset(display_data, 0, sizeof(display_data));
}

void display() {
  if (!display_switch) return;

  // Check if display controller is ready
  if (!Wire.requestFrom(0x13, 1)) {
    return;
  }
  Wire.read();
  
  for (size_t i = 0; i < 128 / 32; i++) {
    Wire.beginTransmission(0x13);
    Wire.write(display_data + i * 32, 32);
    Wire.endTransmission();
  }

  delay(8); // Minimum delay for screen to function
}

void display_on() {
  display_switch = true;
}

// Turn all pixels black and block further display() calls
void display_off() {
  clear_pixels();
  display();
  display_switch = false;
}

bool display_status() {
  return display_switch;
}
