#pragma once
#include <functional>
#include "buttons.h"

template <class T>
void selection_menu_handle_lr_button(T *selection, std::function<void()> f) {
  button_event_handle(BTN_L, [&] {
    if (static_cast<unsigned int>(*selection) == 0) {
      *selection = T::END;
    } else {
      *selection = static_cast<T>(static_cast<unsigned int>(*selection) - 1);
    }
    f();
  });
  button_event_handle(BTN_R, [&] {
    if (*selection == T::END) {
      *selection = static_cast<T>(0);
    } else {
      *selection = static_cast<T>(static_cast<unsigned int>(*selection) + 1);
    }
    f();
  });
}