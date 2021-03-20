#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "babytiger_emu.h"


struct matrix_display gDisplay = {NULL, NULL, NULL};
Pixel pixels[NUM_PIXELS];


enum snake_direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

struct snake_position {
  unsigned short x : 4;
  unsigned short y : 4;
  struct snake_position* next;
};


int main() {
  if (!setup()) {
    return 1;
  }

  // Initial snake status
  enum snake_direction direction = LEFT;
  struct snake_position* headPos = malloc(sizeof(struct snake_position));
  headPos->x = 8;
  headPos->y = 8;
  headPos->next = malloc(sizeof(struct snake_position));
  headPos->next->x = 9;
  headPos->next->y = 8;
  headPos->next->next = NULL;
  bool foodEaten = true;
  struct snake_position foodPos = {0, 0, NULL};

  SDL_Event event = {};

  bool quit = false;
  while (!quit) {

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_LEFT:
              if (direction != RIGHT) direction = LEFT;
              break;
            case SDLK_RIGHT:
              if (direction != LEFT) direction = RIGHT;
              break;
            case SDLK_UP:
              if (direction != DOWN) direction = UP;
              break;
            case SDLK_DOWN:
              if (direction != UP) direction = DOWN;
              break;
          }
          break;
      }
    }

    // Move head
    struct snake_position* newHeadPos = malloc(sizeof(struct snake_position));
    newHeadPos->next = headPos;
    switch (direction) {
      case UP:
        newHeadPos->x = headPos->x;
        newHeadPos->y = (headPos->y - 1) % 16;
        break;
      case DOWN:
        newHeadPos->x = headPos->x;
        newHeadPos->y = (headPos->y + 1) % 16;
        break;
      case LEFT:
        newHeadPos->x = (headPos->x - 1) % 16;
        newHeadPos->y = headPos->y;
        break;
      case RIGHT:
        newHeadPos->x = (headPos->x + 1) % 16;
        newHeadPos->y = headPos->y;
        break;
    }

    // Collision check
    if (pixels[XY(newHeadPos->x, newHeadPos->y)].color == COLOR_BLUE) {
      SDL_Log("Game over");
      delay(1000);
      quit = true;
    } else {
      headPos = newHeadPos;

      // Eat food
      if (pixels[XY(newHeadPos->x, newHeadPos->y)].color == COLOR_RED) {
        foodEaten = true;
      }

      if (foodEaten) {
        // Generate new food
        do {
          foodPos.x = rand() / (RAND_MAX / 16);
          foodPos.y = rand() / (RAND_MAX / 16);
        } while (pixels[XY(foodPos.x, foodPos.y)].color == COLOR_BLUE || (foodPos.x == newHeadPos->x && foodPos.y == newHeadPos->y));
        foodEaten = false;
      } else {

        // Move tail
        struct snake_position* tailPos = headPos;
        while (tailPos->next->next) tailPos = tailPos->next;
        free(tailPos->next);
        tailPos->next = NULL;
      }
    }

    // Render
    for (uint16_t i = 0; i < NUM_PIXELS; i++) {
      pixels[i].color = COLOR_BLACK;
    }
    pixels[XY(headPos->x, headPos->y)].color = COLOR_GREEN;
    for (struct snake_position* bodyPos = headPos->next; bodyPos; bodyPos = bodyPos->next) {
      pixels[XY(bodyPos->x, bodyPos->y)].color = COLOR_BLUE;
    }
    pixels[XY(foodPos.x, foodPos.y)].color = COLOR_RED;

    refresh();

    delay(80);
  }
  
  terminate(0);

  return 0;
}


bool setup() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  gDisplay.window = SDL_CreateWindow("BabyTiger Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!gDisplay.window) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window: %s", SDL_GetError());
    return false;
  }

  gDisplay.surface = SDL_GetWindowSurface(gDisplay.window);

  gDisplay.renderer = SDL_CreateRenderer(gDisplay.window, -1, SDL_RENDERER_ACCELERATED);
  if (!gDisplay.renderer) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer: %s", SDL_GetError());
    return false;
  }

  for (uint16_t i = 0; i < NUM_PIXELS; i++) {
    pixels[i].color = COLOR_BLACK;
  }

  refresh();

  return true;
}


void terminate(int status) {
  SDL_DestroyRenderer(gDisplay.renderer);
  SDL_FreeSurface(gDisplay.surface);
  SDL_DestroyWindow(gDisplay.window);
  SDL_Quit();
  exit(status);
}


void delay(uint16_t time) {
  struct timespec ts = {(time_t) (time / 1000), (time % 1000) * 1000000};
  nanosleep(&ts, NULL);
}


void refresh() {
  if (SDL_SetRenderDrawColor(gDisplay.renderer, 0, 0, 0, 255)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to set color to black before RenderClear: %s", SDL_GetError());
  }
  if (SDL_RenderClear(gDisplay.renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "RenderClear error: %s", SDL_GetError());
  }

  for (uint8_t pos_x = 0; pos_x < SCREEN_WIDTH; pos_x++) {
    for (uint8_t pos_y = 0; pos_y < SCREEN_HEIGHT; pos_y++) {
      uint32_t color = pixels[XY(pos_x, pos_y)].color;
      if (SDL_SetRenderDrawColor(gDisplay.renderer, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to set color to 0x%08x before drawing circle: %s", color, SDL_GetError());
      }

      // Draw circle
      for (int i = 0; i < WINDOW_WIDTH / SCREEN_WIDTH; i++) {
        for (int j = 0; j < WINDOW_HEIGHT / SCREEN_HEIGHT; j++) {
          if (square(i - WINDOW_WIDTH / SCREEN_WIDTH / 2) + square(j - WINDOW_HEIGHT / SCREEN_HEIGHT / 2)  - square(CIRCLE_RADIUS) <= 0) {
            if (SDL_RenderDrawPoint(gDisplay.renderer, pos_x * WINDOW_WIDTH / SCREEN_WIDTH + i, pos_y * WINDOW_HEIGHT / SCREEN_HEIGHT + j)) {
              SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error while drawing circle: %s", SDL_GetError());
            }
          }
        }
      }
    }
  }

  SDL_RenderPresent(gDisplay.renderer);
}


uint16_t XY(uint8_t x, uint8_t y) {
  return y * SCREEN_WIDTH + x;
}


int square(int x) {
  return x * x;
}
