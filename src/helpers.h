#ifndef HELPERS_H
#define HELPERS_H

#include <pebble.h>

#define RED    0
#define GREEN  1
#define BLUE   2
#define YELLOW 3
#define PURPLE 4
#define CYAN   5
#define WHITE  6

#define SQUARE 0
#define LINE   1
#define J      2
#define L      3
#define S      4
#define Z      5
#define T      6

char *itoa10 (int value, char *result);

void update_num_layer (int num, char *str, TextLayer *layer);

void make_block (GPoint *create_block, int type, int bX, int bY);

void rotate_block (GPoint *new_block, GPoint *old_block, int block_type, int rotation);

int find_max_drop (GPoint *block, uint8_t grid[10][20]);

int next_block_offset (int block_type);

#endif
