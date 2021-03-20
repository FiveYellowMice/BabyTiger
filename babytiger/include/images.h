#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>
#include "display.h"

typedef struct {
  uint8_t rows;
  uint8_t columns;
  const uint8_t* data;
} image_t;

namespace images {
  extern const PROGMEM image_t alarm;
  extern const PROGMEM image_t repeat;
}

void draw_image(const image_t* drawing_image_p, int8_t x, int8_t y);