#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 16
#define NUM_PIXELS SCREEN_WIDTH * SCREEN_HEIGHT

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define CIRCLE_RADIUS 19

// Colors
#define COLOR_BLACK    0x00000000
#define COLOR_GRAY     0x7f7f7fff
#define COLOR_WHITE    0xffffffff
#define COLOR_RED      0xff0000ff
#define COLOR_ORANGE   0xff7f00ff
#define COLOR_YELLOW   0xffff00ff
#define COLOR_GREEN    0x00ff00ff
#define COLOR_CYAN     0x00ffffff
#define COLOR_BLUE     0x007fffff
#define COLOR_PURPLE   0x7f00ffff
#define COLOR_MAGENTA  0xff00ffff
#define COLOR_PINK     0xff007fff


struct matrix_display {
  SDL_Window* window;
  SDL_Surface* surface;
  SDL_Renderer* renderer;
};

typedef struct {
  uint32_t color;
} Pixel;


bool setup();
void terminate(int status);

void delay(uint16_t time);
void refresh();

uint16_t XY(uint8_t x, uint8_t y);
int square(int x);
