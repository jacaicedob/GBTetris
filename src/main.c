
#include <gb/gb.h>
#include <gbdk/font.h>
#include <stdint.h>
#include <rand.h>

#include "structs.h"
#include "cube_sprite_py.h"

/*
  Copied from Black Castle github (global.h)
  https://github.com/untoxa/BlackCastle
*/
#define UPDATE_KEYS()   old_input = input; input = joypad()
#define KEY_TICKED(K)   ((input & (K)) && !(old_input & (K)))


void create_line_block(struct Block *block, uint8_t x, uint8_t y, char orientation_idx){
  uint8_t spriteid = 0;

  block->n_orientations = 3;
  block->orientation_idx = orientation_idx;
  block->x = x;
  block->y = y;

  switch (orientation_idx)
  {
    case 0:
      // Flat
      block->sp1.spriteid = spriteid;
      block->sp1.x = x;
      block->sp1.y = y;
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = block->sp1.x + 8;
      block->sp2.y = block->sp1.y;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x + 8;
      block->sp3.y = block->sp2.y;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x + 8;
      block->sp4.y = block->sp3.y;
      break;

    case 1:
      // Clockwise
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = x;
      block->sp4.y = y;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp4.x;
      block->sp3.y = block->sp4.y - 8;
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = block->sp3.x;
      block->sp2.y = block->sp3.y - 8;
      block->sp1.spriteid = spriteid;
      block->sp1.x = block->sp2.x;
      block->sp1.y = block->sp2.y - 8;
      break;

    case 2:
      // Counter clockwise
      block->sp1.spriteid = spriteid;
      block->sp1.x = x;
      block->sp1.y = y;
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = block->sp1.x;
      block->sp2.y = block->sp1.y - 8;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x;
      block->sp3.y = block->sp2.y - 8;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x;
      block->sp4.y = block->sp3.y - 8;
      break;

    default:
      break;
  }

  // Place sprites
  move_sprite(block->sp1.spriteid, block->sp1.x, block->sp1.y);
  move_sprite(block->sp2.spriteid, block->sp2.x, block->sp2.y);
  move_sprite(block->sp3.spriteid, block->sp3.x, block->sp3.y);
  move_sprite(block->sp4.spriteid, block->sp4.x, block->sp4.y);
}

void create_square_block(struct Block *block, uint8_t x, uint8_t y, char orientation_idx){
  uint8_t spriteid = 0;

  block->n_orientations = 1;
  block->orientation_idx = orientation_idx;
  block->x = x;
  block->y = y;

  block->sp3.x = x;
  block->sp3.y = y;
  block->sp4.spriteid = spriteid + 3;
  block->sp4.x = block->sp3.x + 8;
  block->sp4.y = block->sp3.y;
  block->sp1.spriteid = spriteid;
  block->sp1.x = block->sp3.x;
  block->sp1.y = block->sp3.y - 8;
  block->sp2.spriteid = spriteid + 1;
  block->sp2.x = block->sp1.x + 8;
  block->sp2.y = block->sp1.y;
  block->sp3.spriteid = spriteid + 2;

  // Place sprites
  move_sprite(block->sp1.spriteid, block->sp1.x, block->sp1.y);
  move_sprite(block->sp2.spriteid, block->sp2.x, block->sp2.y);
  move_sprite(block->sp3.spriteid, block->sp3.x, block->sp3.y);
  move_sprite(block->sp4.spriteid, block->sp4.x, block->sp4.y);
}

void create_l1_block(struct Block *block, uint8_t x, uint8_t y, char orientation_idx){
  uint8_t spriteid = 0;

  block->n_orientations = 4;
  block->orientation_idx = orientation_idx;
  block->x = x;
  block->y = y;

  switch (orientation_idx)
  {
    case 0:
      // Initial
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = x;
      block->sp2.y = y;
      block->sp1.spriteid = spriteid;
      block->sp1.x = block->sp2.x;
      block->sp1.y = block->sp2.y - 8;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x + 8;
      block->sp3.y = block->sp2.y;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x + 8;
      block->sp4.y = block->sp3.y;
      break;
    
    case 1:
      // First clockwise rotation
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = x;
      block->sp2.y = y;
      block->sp1.spriteid = spriteid;
      block->sp1.x = block->sp2.x + 8;
      block->sp1.y = block->sp2.y;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x;
      block->sp3.y = block->sp2.y + 8;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x;
      block->sp4.y = block->sp3.y + 8;
      break;

    case 2:
      // Second clockwise rotation 
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = x;
      block->sp2.y = y;
      block->sp1.spriteid = spriteid;
      block->sp1.x = block->sp2.x;
      block->sp1.y = block->sp2.y + 8;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x - 8;
      block->sp3.y = block->sp2.y;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x - 8;
      block->sp4.y = block->sp3.y;
      break;

    case 3: 
      // Last clockwise rotation
      block->sp2.spriteid = spriteid + 1;
      block->sp2.x = x;
      block->sp2.y = y;
      block->sp1.spriteid = spriteid;
      block->sp1.x = block->sp2.x - 8;
      block->sp1.y = block->sp2.y;
      block->sp3.spriteid = spriteid + 2;
      block->sp3.x = block->sp2.x;
      block->sp3.y = block->sp2.y - 8;
      block->sp4.spriteid = spriteid + 3;
      block->sp4.x = block->sp3.x;
      block->sp4.y = block->sp3.y - 8;
      break;

    default:
      break;
  }

  // Place sprites
  move_sprite(block->sp1.spriteid, block->sp1.x, block->sp1.y);
  move_sprite(block->sp2.spriteid, block->sp2.x, block->sp2.y);
  move_sprite(block->sp3.spriteid, block->sp3.x, block->sp3.y);
  move_sprite(block->sp4.spriteid, block->sp4.x, block->sp4.y);
}

void create_l2_block(struct Block *block, uint8_t x, uint8_t y, char orientation_idx){
  uint8_t spriteid = 0;

  block->n_orientations = 4;
  block->orientation_idx = orientation_idx;
  block->x = x;
  block->y = y;

  switch (orientation_idx)
  {
  case 0:
    // Initial
    block->sp2.spriteid = spriteid + 1;
    block->sp2.x = x;
    block->sp2.y = y;
    block->sp1.spriteid = spriteid;
    block->sp1.x = block->sp2.x;
    block->sp1.y = block->sp2.y - 8;
    block->sp3.spriteid = spriteid + 2;
    block->sp3.x = block->sp2.x - 8;
    block->sp3.y = block->sp2.y;
    block->sp4.spriteid = spriteid + 3;
    block->sp4.x = block->sp3.x - 8;
    block->sp4.y = block->sp3.y;
    break;
  
  case 1:
    // First clockwise rotation
    block->sp2.spriteid = spriteid + 1;
    block->sp2.x = x;
    block->sp2.y = y;
    block->sp1.spriteid = spriteid;
    block->sp1.x = block->sp2.x + 8;
    block->sp1.y = block->sp2.y;
    block->sp3.spriteid = spriteid + 2;
    block->sp3.x = block->sp2.x;
    block->sp3.y = block->sp2.y - 8;
    block->sp4.spriteid = spriteid + 3;
    block->sp4.x = block->sp3.x;
    block->sp4.y = block->sp3.y - 8;
    break;

  case 2:
    // Second clockwise rotation 
    block->sp2.spriteid = spriteid + 1;
    block->sp2.x = x;
    block->sp2.y = y;
    block->sp1.spriteid = spriteid;
    block->sp1.x = block->sp2.x;
    block->sp1.y = block->sp2.y + 8;
    block->sp3.spriteid = spriteid + 2;
    block->sp3.x = block->sp2.x + 8;
    block->sp3.y = block->sp2.y;
    block->sp4.spriteid = spriteid + 3;
    block->sp4.x = block->sp3.x + 8;
    block->sp4.y = block->sp3.y;
    break;

  case 3: 
    // Last clockwise rotation
    block->sp2.spriteid = spriteid + 1;
    block->sp2.x = x;
    block->sp2.y = y;
    block->sp1.spriteid = spriteid;
    block->sp1.x = block->sp2.x - 8;
    block->sp1.y = block->sp2.y;
    block->sp3.spriteid = spriteid + 2;
    block->sp3.x = block->sp2.x;
    block->sp3.y = block->sp2.y + 8;
    block->sp4.spriteid = spriteid + 3;
    block->sp4.x = block->sp3.x;
    block->sp4.y = block->sp3.y + 8;
    break;

  default:
    break;
  }

  // Place sprites
  move_sprite(block->sp1.spriteid, block->sp1.x, block->sp1.y);
  move_sprite(block->sp2.spriteid, block->sp2.x, block->sp2.y);
  move_sprite(block->sp3.spriteid, block->sp3.x, block->sp3.y);
  move_sprite(block->sp4.spriteid, block->sp4.x, block->sp4.y);
}

void get_block(struct Block *block, uint8_t block_type, uint8_t x, uint8_t y, char orientation_idx){
  /*
    Block type 0: Line, 
                1: Square
                2: L1
                3: L2
  */
  
  switch (block_type)
  {
    case 0:
      create_line_block(block, x, y, orientation_idx);
      break;

    case 1:
      create_square_block(block, x, y, orientation_idx);
      break;

    case 2:
      create_l1_block(block, x, y, orientation_idx);
      break;

    case 3:
      create_l2_block(block, x, y, orientation_idx);
      break;

    default:
      break;
  }
}

uint8_t get_random_block_type(void){
  // Returns a random block type (0 - 4)
  initrand(DIV_REG);
  uint8_t randn;

  randn = rand(); // [0 - 255]
  randn = rand(); // [0 - 255]

  if (randn < 64) {
    return 0;
  }
  else if (randn < 128){
    return 1;
  }
  else if (randn < 192){
    return 2;
  }
  else {
    return 3;
  }
}

void main(void){
  uint8_t input;
  uint8_t old_input;

  uint8_t x;
  uint8_t y;

  struct Block current_block;
  uint8_t current_block_type;  // 0: Line, 1: Square, 2: L1, 3: L2
  int8_t current_orientation_idx;

  // struct Block next_block;
  // uint8_t next_block_type;  // 0: Line, 1: Square, 2: L1, 3: L2

  // Load sprite data
  set_sprite_data(0,1,cube_sprite_data);
  set_sprite_data(1,1,cube_sprite_data);
  set_sprite_data(2,1,cube_sprite_data);
  set_sprite_data(3,1,cube_sprite_data);

  // Load start values
  x = 80;
  y = 80;
  current_block_type = 0;
  current_orientation_idx = 0;
  get_block(&current_block, current_block_type, x, y, current_orientation_idx);
  
  input = 0x0;

  // Turn on display and show sprites
  DISPLAY_ON;
  SHOW_SPRITES;
  initrand(DIV_REG);

  while (1){
    // Game loop
    UPDATE_KEYS();

    if (KEY_TICKED(J_A)){
      // Clockwise rotation
      switch (current_block_type)
      {
        case 0:
          //  Line block clockwise rotation toggles between indices 0 and 1
          // Pivots around sp4
          if (current_block.orientation_idx == 0){
            current_orientation_idx = 1;
            get_block(&current_block, current_block_type, current_block.sp4.x, current_block.sp4.y, current_orientation_idx);
          }
          else if (current_orientation_idx == 1) {
            current_orientation_idx = 0;
            get_block(&current_block, current_block_type, current_block.sp4.x - 24, current_block.sp4.y, current_orientation_idx);
          }
          break;
        
        case 1:
          // Square block does not rotate
          break;

        case 2:  // Same logic for L2, L3
        case 3:
          current_orientation_idx++;
          if (current_orientation_idx >= current_block.n_orientations){
            current_orientation_idx = 0;
          }
          get_block(&current_block, current_block_type, current_block.sp2.x, current_block.sp2.y, current_orientation_idx);

        default:
          break;
      }
    }
    if (KEY_TICKED(J_B)){
        // Counter-clockwise rotation
        switch (current_block_type)
        {
        case 0:
          //  Line block counter-clockwise rotation toggles between indices 0 and 2
          // Pivots around sp1
          if (current_block.orientation_idx == 0){
            current_orientation_idx = 2;
            get_block(&current_block, current_block_type, current_block.sp1.x, current_block.sp1.y, current_orientation_idx);
          }
          else if (current_orientation_idx == 2) {
            current_orientation_idx = 0;
            get_block(&current_block, current_block_type, current_block.sp1.x, current_block.sp1.y, current_orientation_idx);
          }
          break;

        case 1:
          // Square block does not rotate
          break;

        case 2:  // Same logic for both L1,L2
        case 3:
          current_orientation_idx--;
          if (current_orientation_idx < 0){
            current_orientation_idx = current_block.n_orientations - 1;
          }
          get_block(&current_block, current_block_type, current_block.sp2.x, current_block.sp2.y, current_orientation_idx);
      
        default:
            break;
        }
    }
    if (KEY_TICKED(J_SELECT)){
      current_block_type++;
      if (current_block_type > 3){
        current_block_type = 0;
      }
      current_orientation_idx = 0;
      get_block(&current_block, current_block_type, x, y, current_orientation_idx);
    }
    if (KEY_TICKED(J_START)){
      current_block_type = get_random_block_type();
      current_orientation_idx = 0;
      get_block(&current_block, current_block_type, x, y, current_orientation_idx);
    }

    wait_vbl_done();
  }
}