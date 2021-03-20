#include <stdint.h>
#include <avr/pgmspace.h>
#include "display.h"
#include "fonts.h"


namespace fonts {

  const PROGMEM uint8_t ascii7_space[]  = {0b00000000, 0b00000000};
  const PROGMEM uint8_t ascii7_exclam[] = {0b01011111};
  const PROGMEM uint8_t ascii7_quot[]   = {0b00000011, 0b00000000, 0b00000011};
  const PROGMEM uint8_t ascii7_hash[]   = {0b00010100, 0b01111111, 0b00010100, 0b01111111, 0b00010100};
  const PROGMEM uint8_t ascii7_dollar[] = {0b00100110, 0b01001001, 0b01111111, 0b01001001, 0b00110010};
  const PROGMEM uint8_t ascii7_perc[]   = {0b01100011, 0b00010011, 0b00001000, 0b01100100, 0b01100011};
  const PROGMEM uint8_t ascii7_and[]    = {0b00110110, 0b01001001, 0b01010001, 0b00110010, 0b01001000};
  const PROGMEM uint8_t ascii7_apos[]   = {0b00000011};
  const PROGMEM uint8_t ascii7_lparen[] = {0b00011100, 0b00100010, 0b01000001};
  const PROGMEM uint8_t ascii7_rparen[] = {0b01000001, 0b00100010, 0b00011100};
  const PROGMEM uint8_t ascii7_aster[]  = {0b00101000, 0b00011100, 0b00101000};
  const PROGMEM uint8_t ascii7_plus[]   = {0b00001000, 0b00011100, 0b00001000};
  const PROGMEM uint8_t ascii7_comma[]  = {0b01000000, 0b01100000};
  const PROGMEM uint8_t ascii7_dash[]   = {0b00001000, 0b00001000, 0b00001000};
  const PROGMEM uint8_t ascii7_period[] = {0b01000000};
  const PROGMEM uint8_t ascii7_slash[]  = {0b01100000, 0b00011100, 0b00000011};
  const PROGMEM uint8_t ascii7_0[]      = {0b00111110, 0b01000101, 0b01011001, 0b00111110};
  const PROGMEM uint8_t ascii7_1[]      = {0b00000000, 0b01000010, 0b01111111, 0b01000000};
  const PROGMEM uint8_t ascii7_2[]      = {0b01100010, 0b01010001, 0b01001001, 0b01000110};
  const PROGMEM uint8_t ascii7_3[]      = {0b00100010, 0b01001001, 0b01001001, 0b00110110};
  const PROGMEM uint8_t ascii7_4[]      = {0b00001100, 0b00001010, 0b00001001, 0b01111111};
  const PROGMEM uint8_t ascii7_5[]      = {0b00101111, 0b01001001, 0b01001001, 0b00110001};
  const PROGMEM uint8_t ascii7_6[]      = {0b00111110, 0b01001001, 0b01001001, 0b00110010};
  const PROGMEM uint8_t ascii7_7[]      = {0b00000001, 0b01111001, 0b00000101, 0b00000011};
  const PROGMEM uint8_t ascii7_8[]      = {0b00110110, 0b01001001, 0b01001001, 0b00110110};
  const PROGMEM uint8_t ascii7_9[]      = {0b00100110, 0b01001001, 0b01001001, 0b00111110};
  const PROGMEM uint8_t ascii7_colon[]  = {0b00100100};
  const PROGMEM uint8_t ascii7_semico[] = {0b01000000, 0b00100100};
  const PROGMEM uint8_t ascii7_lt[]     = {0b00010000, 0b00101000, 0b01000100};
  const PROGMEM uint8_t ascii7_equal[]  = {0b00010100, 0b00010100, 0b00010100};
  const PROGMEM uint8_t ascii7_gt[]     = {0b01000100, 0b00101000, 0b00010000};
  const PROGMEM uint8_t ascii7_quest[]  = {0b00000010, 0b01011001, 0b00000110};
  const PROGMEM uint8_t ascii7_at[]     = {0b00111000, 0b01000100, 0b01110100, 0b00111000};
  const PROGMEM uint8_t ascii7_cap_a[]  = {0b01111110, 0b00001001, 0b00001001, 0b01111110};
  const PROGMEM uint8_t ascii7_cap_b[]  = {0b01111111, 0b01001001, 0b01001001, 0b00110110};
  const PROGMEM uint8_t ascii7_cap_c[]  = {0b00111110, 0b01000001, 0b01000001, 0b00100010};
  const PROGMEM uint8_t ascii7_cap_d[]  = {0b01111111, 0b01000001, 0b01000001, 0b00111110};
  const PROGMEM uint8_t ascii7_cap_e[]  = {0b01111111, 0b01001001, 0b01001001, 0b01000001};
  const PROGMEM uint8_t ascii7_cap_f[]  = {0b01111111, 0b00001001, 0b00001001, 0b00000001};
  const PROGMEM uint8_t ascii7_cap_g[]  = {0b00111110, 0b01000001, 0b01001001, 0b00111010};
  const PROGMEM uint8_t ascii7_cap_h[]  = {0b01111111, 0b00001000, 0b00001000, 0b01111111};
  const PROGMEM uint8_t ascii7_cap_i[]  = {0b01000001, 0b01111111, 0b01000001};
  const PROGMEM uint8_t ascii7_cap_j[]  = {0b00100000, 0b01000000, 0b00111111};
  const PROGMEM uint8_t ascii7_cap_k[]  = {0b01111111, 0b00001000, 0b00010100, 0b01000001};
  const PROGMEM uint8_t ascii7_cap_l[]  = {0b01111111, 0b01000000, 0b01000000, 0b01000000};
  const PROGMEM uint8_t ascii7_cap_m[]  = {0b01111111, 0b00000010, 0b00001100, 0b00000010, 0b01111111};
  const PROGMEM uint8_t ascii7_cap_n[]  = {0b01111111, 0b00000010, 0b00011100, 0b00100000, 0b01111111};
  const PROGMEM uint8_t ascii7_cap_o[]  = {0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00111110};
  const PROGMEM uint8_t ascii7_cap_p[]  = {0b01111111, 0b00001001, 0b00001001, 0b00000110};
  const PROGMEM uint8_t ascii7_cap_q[]  = {0b00111110, 0b01000001, 0b01010001, 0b00100001, 0b01011110};
  const PROGMEM uint8_t ascii7_cap_r[]  = {0b01111111, 0b00011001, 0b00101001, 0b01000110};
  const PROGMEM uint8_t ascii7_cap_s[]  = {0b00100110, 0b01001001, 0b01001001, 0b00110010};
  const PROGMEM uint8_t ascii7_cap_t[]  = {0b00000001, 0b00000001, 0b01111111, 0b00000001, 0b00000001};
  const PROGMEM uint8_t ascii7_cap_u[]  = {0b00111111, 0b01000000, 0b01000000, 0b00111111};
  const PROGMEM uint8_t ascii7_cap_v[]  = {0b00000111, 0b00011000, 0b01100000, 0b00011000, 0b00000111};
  const PROGMEM uint8_t ascii7_cap_w[]  = {0b00011111, 0b01100000, 0b00011000, 0b01100000, 0b00011111};
  const PROGMEM uint8_t ascii7_cap_x[]  = {0b01100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011};
  const PROGMEM uint8_t ascii7_cap_y[]  = {0b00000011, 0b00000100, 0b01111000, 0b00000100, 0b00000011};
  const PROGMEM uint8_t ascii7_cap_z[]  = {0b01100001, 0b01010001, 0b01001001, 0b01000101, 0b01000011};
  const PROGMEM uint8_t ascii7_lsqbr[]  = {0b01111111, 0b01000001};
  const PROGMEM uint8_t ascii7_bslash[] = {0b00000011, 0b00011100, 0b01100000};
  const PROGMEM uint8_t ascii7_rsqbr[]  = {0b01000001, 0b01111111};
  const PROGMEM uint8_t ascii7_caret[]  = {0b00000010, 0b00000001, 0b00000010};
  const PROGMEM uint8_t ascii7_udrscr[] = {0b01000000, 0b01000000, 0b01000000};
  const PROGMEM uint8_t ascii7_grave[]  = {0b00000001, 0b00000010};
  const PROGMEM uint8_t ascii7_a[]      = {0b00100000, 0b01010100, 0b01010100, 0b01111000};
  const PROGMEM uint8_t ascii7_b[]      = {0b01111110, 0b01001000, 0b01001000, 0b00110000};
  const PROGMEM uint8_t ascii7_c[]      = {0b00110000, 0b01001000, 0b01001000};
  const PROGMEM uint8_t ascii7_d[]      = {0b00110000, 0b01001000, 0b01001000, 0b01111110};
  const PROGMEM uint8_t ascii7_e[]      = {0b00111000, 0b01010100, 0b01010100, 0b00011000};
  const PROGMEM uint8_t ascii7_f[]      = {0b00001000, 0b01111100, 0b00001010};
  const PROGMEM uint8_t ascii7_g[]      = {0b01001000, 0b01010100, 0b01010100, 0b00111100};
  const PROGMEM uint8_t ascii7_h[]      = {0b01111110, 0b00001000, 0b00001000, 0b01110000};
  const PROGMEM uint8_t ascii7_i[]      = {0b01111010};
  const PROGMEM uint8_t ascii7_j[]      = {0b01000000, 0b00111010};
  const PROGMEM uint8_t ascii7_k[]      = {0b01111110, 0b00100000, 0b01010000};
  const PROGMEM uint8_t ascii7_l[]      = {0b01111111};
  const PROGMEM uint8_t ascii7_m[]      = {0b01111000, 0b00001000, 0b01110000, 0b00001000, 0b01110000};
  const PROGMEM uint8_t ascii7_n[]      = {0b01111000, 0b00001000, 0b00001000, 0b01110000};
  const PROGMEM uint8_t ascii7_o[]      = {0b00110000, 0b01001000, 0b01001000, 0b00110000};
  const PROGMEM uint8_t ascii7_p[]      = {0b01111100, 0b00010100, 0b00001000};
  const PROGMEM uint8_t ascii7_q[]      = {0b00001000, 0b00010100, 0b01111100};
  const PROGMEM uint8_t ascii7_r[]      = {0b01111100, 0b00001000, 0b00000100};
  const PROGMEM uint8_t ascii7_s[]      = {0b01001000, 0b01010100, 0b01010100, 0b00100100};
  const PROGMEM uint8_t ascii7_t[]      = {0b00001000, 0b01111100, 0b01001000};
  const PROGMEM uint8_t ascii7_u[]      = {0b00111000, 0b01000000, 0b01000000, 0b00111000};
  const PROGMEM uint8_t ascii7_v[]      = {0b00011000, 0b01100000, 0b00011000};
  const PROGMEM uint8_t ascii7_w[]      = {0b00111000, 0b01000000, 0b00111000, 0b01000000, 0b00111000};
  const PROGMEM uint8_t ascii7_x[]      = {0b01001000, 0b00110000, 0b01001000};
  const PROGMEM uint8_t ascii7_y[]      = {0b01000110, 0b01001000, 0b00101000, 0b00011110};
  const PROGMEM uint8_t ascii7_z[]      = {0b01001000, 0b01101000, 0b01011000, 0b01001000};
  const PROGMEM uint8_t ascii7_lbrace[] = {0b00001000, 0b00110110, 0b01000001};
  const PROGMEM uint8_t ascii7_pipe[]   = {0b01111111};
  const PROGMEM uint8_t ascii7_rbrace[] = {0b01000001, 0b00110110, 0b00001000};
  const PROGMEM uint8_t ascii7_tilde[]  = {0b00001000, 0b00000100, 0b00001000, 0b00010000, 0b00001000};
  const PROGMEM glyph8_t ascii7[] = {
    {2, ascii7_space},
    {1, ascii7_exclam},
    {3, ascii7_quot},
    {5, ascii7_hash},
    {5, ascii7_dollar},
    {5, ascii7_perc},
    {5, ascii7_and},
    {1, ascii7_apos},
    {3, ascii7_lparen},
    {3, ascii7_rparen},
    {3, ascii7_aster},
    {3, ascii7_plus},
    {2, ascii7_comma},
    {3, ascii7_dash},
    {1, ascii7_period},
    {3, ascii7_slash},
    {4, ascii7_0},
    {4, ascii7_1},
    {4, ascii7_2},
    {4, ascii7_3},
    {4, ascii7_4},
    {4, ascii7_5},
    {4, ascii7_6},
    {4, ascii7_7},
    {4, ascii7_8},
    {4, ascii7_9},
    {1, ascii7_colon},
    {2, ascii7_semico},
    {3, ascii7_lt},
    {3, ascii7_equal},
    {3, ascii7_gt},
    {3, ascii7_quest},
    {4, ascii7_at},
    {4, ascii7_cap_a},
    {4, ascii7_cap_b},
    {4, ascii7_cap_c},
    {4, ascii7_cap_d},
    {4, ascii7_cap_e},
    {4, ascii7_cap_f},
    {4, ascii7_cap_g},
    {4, ascii7_cap_h},
    {3, ascii7_cap_i},
    {3, ascii7_cap_j},
    {4, ascii7_cap_k},
    {4, ascii7_cap_l},
    {5, ascii7_cap_m},
    {5, ascii7_cap_n},
    {5, ascii7_cap_o},
    {4, ascii7_cap_p},
    {5, ascii7_cap_q},
    {4, ascii7_cap_r},
    {4, ascii7_cap_s},
    {5, ascii7_cap_t},
    {4, ascii7_cap_u},
    {5, ascii7_cap_v},
    {5, ascii7_cap_w},
    {5, ascii7_cap_x},
    {5, ascii7_cap_y},
    {5, ascii7_cap_z},
    {2, ascii7_lsqbr},
    {3, ascii7_bslash},
    {2, ascii7_rsqbr},
    {3, ascii7_caret},
    {3, ascii7_udrscr},
    {2, ascii7_grave},
    {4, ascii7_a},
    {4, ascii7_b},
    {3, ascii7_c},
    {4, ascii7_d},
    {4, ascii7_e},
    {3, ascii7_f},
    {4, ascii7_g},
    {4, ascii7_h},
    {1, ascii7_i},
    {2, ascii7_j},
    {3, ascii7_k},
    {1, ascii7_l},
    {5, ascii7_m},
    {4, ascii7_n},
    {4, ascii7_o},
    {3, ascii7_p},
    {3, ascii7_q},
    {3, ascii7_r},
    {4, ascii7_s},
    {3, ascii7_t},
    {4, ascii7_u},
    {3, ascii7_v},
    {5, ascii7_w},
    {3, ascii7_x},
    {4, ascii7_y},
    {4, ascii7_z},
    {3, ascii7_lbrace},
    {1, ascii7_pipe},
    {3, ascii7_rbrace},
    {5, ascii7_tilde},
  };

  const PROGMEM uint8_t digits5_space[]  = {0b00000000, 0b00000000, 0b00000000};
  const PROGMEM uint8_t digits5_plus[]   = {0b00000100, 0b00001110, 0b00000100};
  const PROGMEM uint8_t digits5_dash[]   = {0b00000100, 0b00000100};
  const PROGMEM uint8_t digits5_period[] = {0b00010000};
  const PROGMEM uint8_t digits5_slash[]  = {0b00011000, 0b00000111};
  const PROGMEM uint8_t digits5_0[]      = {0b00011111, 0b00010001, 0b00011111};
  const PROGMEM uint8_t digits5_1[]      = {0b00010010, 0b00011111, 0b00010000};
  const PROGMEM uint8_t digits5_2[]      = {0b00011101, 0b00010101, 0b00010111};
  const PROGMEM uint8_t digits5_3[]      = {0b00010101, 0b00010101, 0b00011111};
  const PROGMEM uint8_t digits5_4[]      = {0b00001100, 0b00001010, 0b00011111};
  const PROGMEM uint8_t digits5_5[]      = {0b00010111, 0b00010101, 0b00011101};
  const PROGMEM uint8_t digits5_6[]      = {0b00011111, 0b00010101, 0b00011101};
  const PROGMEM uint8_t digits5_7[]      = {0b00000001, 0b00011101, 0b00000011};
  const PROGMEM uint8_t digits5_8[]      = {0b00011111, 0b00010101, 0b00011111};
  const PROGMEM uint8_t digits5_9[]      = {0b00010111, 0b00010101, 0b00011111};
  const PROGMEM uint8_t digits5_colon[]  = {0b00001010};
  const PROGMEM uint8_t digits5_cap_a[]  = {0b00011110, 0b00000101, 0b00011110};
  const PROGMEM uint8_t digits5_cap_b[]  = {0b00011111, 0b00010101, 0b00001010};
  const PROGMEM uint8_t digits5_cap_c[]  = {0b00001110, 0b00010001, 0b00010001};
  const PROGMEM uint8_t digits5_cap_d[]  = {0b00011111, 0b00010001, 0b00001110};
  const PROGMEM uint8_t digits5_cap_e[]  = {0b00011111, 0b00010101, 0b00010001};
  const PROGMEM uint8_t digits5_cap_f[]  = {0b00011111, 0b00000101, 0b00000001};
  const PROGMEM uint8_t digits5_cap_p[]  = {0b00011111, 0b00000101, 0b00000010};
  const PROGMEM uint8_t digits5_cap_r[]  = {0b00011111, 0b00000101, 0b00011010};
  const PROGMEM uint8_t digits5_cap_s[]  = {0b00010010, 0b00010101, 0b00001001};
  const PROGMEM uint8_t digits5_cap_t[]  = {0b00000001, 0b00011111, 0b00000001};
  const PROGMEM uint8_t digits5_cap_u[]  = {0b00011111, 0b00010000, 0b00011111};
  const PROGMEM uint8_t digits5_udrscr[] = {0b00010000, 0b00010000, 0b00010000};
  const PROGMEM glyph8_t digits5[] = {
    {3, digits5_space},
    {3, digits5_plus},
    {3, digits5_space}, // colon
    {2, digits5_dash},
    {1, digits5_period},
    {2, digits5_slash},
    {3, digits5_0},
    {3, digits5_1},
    {3, digits5_2},
    {3, digits5_3},
    {3, digits5_4},
    {3, digits5_5},
    {3, digits5_6},
    {3, digits5_7},
    {3, digits5_8},
    {3, digits5_9},
    {1, digits5_colon},
    {3, digits5_space}, // semico
    {3, digits5_space}, // lt
    {3, digits5_space}, // equal
    {3, digits5_space}, // gt
    {3, digits5_space}, // quest
    {3, digits5_space}, // at
    {3, digits5_cap_a},
    {3, digits5_cap_b},
    {3, digits5_cap_c},
    {3, digits5_cap_d},
    {3, digits5_cap_e},
    {3, digits5_cap_f},
    {3, digits5_space}, // cap_g
    {3, digits5_space}, // cap_h
    {3, digits5_space}, // cap_i
    {3, digits5_space}, // cap_j
    {3, digits5_space}, // cap_k
    {3, digits5_space}, // cap_l
    {3, digits5_space}, // cap_m
    {3, digits5_space}, // cap_n
    {3, digits5_space}, // cap_o
    {3, digits5_cap_p},
    {3, digits5_space}, // cap_q
    {3, digits5_cap_r},
    {3, digits5_cap_s},
    {3, digits5_cap_t},
    {3, digits5_cap_u},
    {3, digits5_space}, // cap_v
    {3, digits5_space}, // cap_w
    {3, digits5_space}, // cap_x
    {3, digits5_space}, // cap_y
    {3, digits5_space}, // cap_z
    {3, digits5_space}, // lsqbr
    {3, digits5_space}, // bslash
    {3, digits5_space}, // rsqbr
    {3, digits5_space}, // caret
    {3, digits5_udrscr},
  };

  const PROGMEM uint8_t week_su_c[] = {0b00001010, 0b00001101, 0b00000101, 0b00000000, 0b00001111, 0b00001000, 0b00001111};
  const PROGMEM glyph8_t week_su = {7, week_su_c};
  const PROGMEM uint8_t week_mo_c[] = {0b00001110, 0b00000110, 0b00001110, 0b00000000, 0b00001110, 0b00001010, 0b00001110};
  const PROGMEM glyph8_t week_mo = {7, week_mo_c};
  const PROGMEM uint8_t week_tu_c[] = {0b00000010, 0b00001110, 0b00000010, 0b00000000, 0b00001110, 0b00001000, 0b00001110};
  const PROGMEM glyph8_t week_tu = {7, week_tu_c};
  const PROGMEM uint8_t week_we_c[] = {0b00001110, 0b00001100, 0b00001110, 0b00000000, 0b00001110, 0b00001110, 0b00001010};
  const PROGMEM glyph8_t week_we = {7, week_we_c};
  const PROGMEM uint8_t week_th_c[] = {0b00000010, 0b00001110, 0b00000010, 0b00000000, 0b00001110, 0b00000100, 0b00001110};
  const PROGMEM glyph8_t week_th = {7, week_th_c};
  const PROGMEM uint8_t week_fr_c[] = {0b00001111, 0b00000101, 0b00000001, 0b00000000, 0b00001110, 0b00000100, 0b00000010};
  const PROGMEM glyph8_t week_fr = {7, week_fr_c};
  const PROGMEM uint8_t week_sa_c[] = {0b00001010, 0b00001101, 0b00000101, 0b00000000, 0b00001110, 0b00000101, 0b00001110};
  const PROGMEM glyph8_t week_sa = {7, week_sa_c};


  const PROGMEM uint8_t deg_celsius_c[] = {0b00000010, 0b00000000, 0b00001110, 0b00001010};
  const PROGMEM glyph8_t deg_celsius = {4, deg_celsius_c};

  const PROGMEM uint8_t hpa_c[] = {0b00001111, 0b00000010, 0b00001100, 0b00000000, 0b00001111, 0b00000101, 0b00000010, 0b00000000, 0b00000100, 0b00001010, 0b00001100};
  const PROGMEM glyph8_t hpa = {11, hpa_c};

  const PROGMEM uint8_t percent_c[] = {0b00001001, 0b00000100, 0b00000010, 0b00001001};
  const PROGMEM glyph8_t percent = {4, percent_c};


  const PROGMEM uint8_t triangle_up_c[] = {0b00000010, 0b00000011, 0b00000010};
  const PROGMEM glyph8_t triangle_up = {3, triangle_up_c};

  const PROGMEM uint8_t triangle_down_c[] = {0b00000001, 0b00000011, 0b00000001};
  const PROGMEM glyph8_t triangle_down = {3, triangle_down_c};

  const PROGMEM uint8_t triangle_left_c[] = {0b00000010, 0b00000111};
  const PROGMEM glyph8_t triangle_left = {2, triangle_left_c};

  const PROGMEM uint8_t triangle_right_c[] = {0b00000111, 0b00000010};
  const PROGMEM glyph8_t triangle_right = {2, triangle_right_c};

  const PROGMEM uint8_t cross_c[] = {0b00000101, 0b00000010, 0b00000101};
  const PROGMEM glyph8_t cross = {3, cross_c};

  const PROGMEM uint8_t circle_c[] = {0b00000010, 0b00000101, 0b00000010};
  const PROGMEM glyph8_t circle = {3, circle_c};


  const PROGMEM uint8_t tick_c[] = {0b00000100, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
  const PROGMEM glyph8_t tick = {5, tick_c};


  const PROGMEM uint8_t quarter_note_c[] = {0b01000000, 0b11100000, 0b11100000, 0b01111111, 0b00000010, 0b00000100};
  const PROGMEM glyph8_t quarter_note = {6, quarter_note_c};

}

// Draw a glyph and return x position of end of the glyph
int8_t draw_glyph(const glyph8_t* drawing_glyph_p, enum COLOR color, int8_t x, int8_t y) {
  glyph8_t drawing_glyph = {0, NULL};
  memcpy_P(&drawing_glyph, drawing_glyph_p, sizeof(glyph8_t));

  for (uint8_t i = 0; i < drawing_glyph.length; i++) {
    uint8_t drawing_column;
    memcpy_P(&drawing_column, drawing_glyph.columns + i, sizeof(uint8_t));
    for (uint8_t j = 0; j < 8; j++) {
      if (drawing_column & (1 << j)) {
        set_pixel(x + i, y + j, color);
      }
    }
  }

  return x + drawing_glyph.length;
}

// Draw text and return x position of where the next character should be, or INT8_MAX if not finished
int8_t draw_text(const char* text, const glyph8_t* font_p, enum COLOR color, int8_t start_x, int8_t start_y) {
  const char* drawing_char_p = text;
  char drawing_char;

  while ((drawing_char = pgm_read_byte_near(drawing_char_p))) {
    if (start_x >= 16) {
      start_x = INT8_MAX;
      break;
    }

    uint8_t glyph_index;
    if (font_p == fonts::ascii7) {
      if (drawing_char <= ' ' || drawing_char > '~') {
        glyph_index = 0; // Treat all control characters and invalid codepoints as space
      } else {
        glyph_index = drawing_char - ' ';
      }
    } else if (font_p == fonts::digits5) {
      if (drawing_char < '+' || drawing_char > '_') {
        glyph_index = 0; // Only 0-9, some capital letters and some symbols are available in this font
      } else {
        glyph_index = drawing_char - '+' + 1;
      }
    } else {
      // Should not happen
      return start_x;
    }

    start_x = draw_glyph(font_p + glyph_index, color, start_x, start_y) + 1;

    drawing_char_p++;
  }

  return start_x;
}
