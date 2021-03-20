#include "images.h"

#define IMAGE_PIXEL_PAIR(a, b) (((uint8_t) COLOR_##a) | (((uint8_t) COLOR_##b) << 4))
#define IMAGE_PIXEL_QUADRUPLET(a, b, c, d) IMAGE_PIXEL_PAIR(a, b), IMAGE_PIXEL_PAIR(c, d)
#define IMAGE_PIXEL_SEXTUPLET(a, b, c, d, e, f) IMAGE_PIXEL_PAIR(a, b), IMAGE_PIXEL_PAIR(c, d), IMAGE_PIXEL_PAIR(e, f)
#define IMAGE_PIXEL_OCTUPLET(a, b, c, d, e, f, g, h) IMAGE_PIXEL_QUADRUPLET(a, b, c, d), IMAGE_PIXEL_QUADRUPLET(e, f, g, h)

namespace images {

  const PROGMEM uint8_t alarm_c[] = {
    IMAGE_PIXEL_OCTUPLET(BLACK, YELLOW, BLACK, RED, RED, RED, BLACK, GRAY),
    IMAGE_PIXEL_OCTUPLET(YELLOW, YELLOW, RED, BLACK, GRAY, BLACK, RED, BLACK),
    IMAGE_PIXEL_OCTUPLET(YELLOW, RED, BLACK, BLACK, BLACK, BLACK, BLACK, RED),
    IMAGE_PIXEL_OCTUPLET(BLACK, RED, WHITE, WHITE, WHITE, BLACK, GRAY, RED),
    IMAGE_PIXEL_OCTUPLET(YELLOW, RED, BLACK, BLACK, WHITE, BLACK, BLACK, RED),
    IMAGE_PIXEL_OCTUPLET(YELLOW, YELLOW, RED, BLACK, GRAY, BLACK, RED, BLACK),
    IMAGE_PIXEL_OCTUPLET(BLACK, YELLOW, BLACK, RED, RED, RED, BLACK, GRAY),
  };
  const PROGMEM image_t alarm = {8, 7, alarm_c};

  const PROGMEM uint8_t repeat_c[] = {
    IMAGE_PIXEL_SEXTUPLET(BLACK, BLACK, MAGENTA, MAGENTA, BLACK, BLACK),
    IMAGE_PIXEL_SEXTUPLET(BLACK, YELLOW, BLACK, BLACK, MAGENTA, BLACK),
    IMAGE_PIXEL_SEXTUPLET(YELLOW, YELLOW, YELLOW, BLACK, MAGENTA, BLACK),
    IMAGE_PIXEL_SEXTUPLET(BLACK, YELLOW, BLACK, BLACK, MAGENTA, BLACK),
    IMAGE_PIXEL_SEXTUPLET(BLACK, YELLOW, BLACK, BLACK, MAGENTA, BLACK),
    IMAGE_PIXEL_SEXTUPLET(BLACK, YELLOW, BLACK, MAGENTA, MAGENTA, MAGENTA),
    IMAGE_PIXEL_SEXTUPLET(BLACK, YELLOW, BLACK, BLACK, MAGENTA, BLACK),
    IMAGE_PIXEL_SEXTUPLET(BLACK, BLACK, YELLOW, YELLOW, BLACK, BLACK),
  };
  const PROGMEM image_t repeat = {6, 8, repeat_c};

}

void draw_image(const image_t* drawing_image_p, int8_t x, int8_t y) {
  image_t drawing_image = {0, 0, NULL};
  memcpy_P(&drawing_image, drawing_image_p, sizeof(image_t));
  if (drawing_image.rows % 2 == 1) {
    // Make rows always even
    drawing_image.rows += 1;
  }

  for (uint8_t i = 0; i < drawing_image.columns; i++) {
    for (uint8_t j = 0; j < drawing_image.rows / 2; j++) {
      uint8_t drawing_pair;
      memcpy_P(&drawing_pair, drawing_image.data + drawing_image.rows / 2 * i + j, sizeof(uint8_t));
      set_pixel(x + i, y + j * 2    , (enum COLOR) ( drawing_pair       & 0x0f));
      set_pixel(x + i, y + j * 2 + 1, (enum COLOR) ((drawing_pair >> 4) & 0x0f));
    }
  }
}