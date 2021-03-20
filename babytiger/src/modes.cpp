#include "modes.h"

Mode* current_mode = nullptr;
Mode* next_mode = nullptr;

void transition_mode(Mode* dst_mode) {
  delete next_mode;
  next_mode = dst_mode;
}