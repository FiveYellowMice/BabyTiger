#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "main.h"

#define NUM_PIXELS 256
#define TRANSFER_DATA_SIZE 128

Adafruit_NeoPixel pixels(256, 5, NEO_GRB + NEO_KHZ800);
uint8_t received_byte_count = 0;

const PROGMEM uint32_t color_to_rgb_map[32] = {
  0x000000, // COLOR_BLACK
  0x404040, // COLOR_GRAY
  0xffffff, // COLOR_WHITE
  0xff0000, // COLOR_RED
  0xff4000, // COLOR_ORANGE
  0xff8000, // COLOR_YELLOW
  0xC0ff00, // COLOR_TENDER_GREEN
  0x00ff00, // COLOR_GREEN
  0x00ffff, // COLOR_CYAN
  0x0040ff, // COLOR_LAKE_BLUE
  0x0000ff, // COLOR_BLUE
  0xff00ff, // COLOR_VIOLET
  0x8000ff, // COLOR_PURPLE
  0xff0080, // COLOR_MAGENTA
  0xff8040, // COLOR_CORAL
  0xff0040, // COLOR_PINK
};

void setup() {
  Serial.begin(9600);

  Wire.begin(0x13);
  Wire.onReceive(i2c_data_receive);

  pixels.begin();
  pixels.setBrightness(4);
}

void loop() {
  if (received_byte_count == TRANSFER_DATA_SIZE) {
    pixels.show();
    received_byte_count = 0;
  }
}

void i2c_data_receive(int num_bytes) {
  while (Wire.available()) {
    if (received_byte_count < TRANSFER_DATA_SIZE) {
      uint8_t received_byte = (uint8_t) Wire.read();
      pixels.setPixelColor(received_byte_count * 2, pgm_read_dword(color_to_rgb_map + ((received_byte >> 4) & 0x0f)));
      pixels.setPixelColor(received_byte_count * 2 + 1, pgm_read_dword(color_to_rgb_map + (received_byte & 0x0f)));
      received_byte_count++;

    } else {
      Wire.read();
    }
  }
}