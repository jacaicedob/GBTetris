#include <gb/gb.h>
#include <stdint.h>

struct Sprite {
  uint8_t spriteid;
  uint8_t x;
  uint8_t y;
};

struct Block {
  uint8_t x;
  uint8_t y;
  char orientation_idx;
  char n_orientations;
  struct Sprite sp1;
  struct Sprite sp2;
  struct Sprite sp3;
  struct Sprite sp4;
};
