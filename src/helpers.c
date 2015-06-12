#include "helpers.h"

/* simple base 10 only itoa */
// Credit: David C. Rankin, Stackoverflow
// Because seriously, the Pebble SDK has no way to do this.
char *itoa10 (int value, char *result)
{
    char const digit[] = "0123456789";
    char *p = result;
    if (value < 0) {
        *p++ = '-';
        value *= -1;
    }

    /* move number of required chars and null terminate */
    int shift = value;
    do {
        ++p;
        shift /= 10;
    } while (shift);
    *p = '\0';

    /* populate result in reverse order */
    do {
        *--p = digit [value % 10];
        value /= 10;
    } while (value);

    return result;
}

void update_num_layer (int num, char* str, TextLayer *layer) {
  itoa10(num, str);
  text_layer_set_text(layer, str);
}

void make_block (GPoint *create_block, int type, int bX, int bY) {
  if (type == SQUARE) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX+1, bY);
    create_block[2] = GPoint(bX, bY+1);
    create_block[3] = GPoint(bX+1, bY+1);
  }
  else if (type == LINE) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX+1, bY);
    create_block[2] = GPoint(bX+2, bY);
    create_block[3] = GPoint(bX+3, bY);
  }
  else if (type == J) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX, bY+1);
    create_block[2] = GPoint(bX+1, bY+1);
    create_block[3] = GPoint(bX+2, bY+1);
  }
  else if (type == L) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX, bY+1);
    create_block[2] = GPoint(bX-1, bY+1);
    create_block[3] = GPoint(bX-2, bY+1);
  }
  else if (type == S) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX-1, bY);
    create_block[2] = GPoint(bX-1, bY+1);
    create_block[3] = GPoint(bX-2, bY+1);
  }
  else if (type == Z) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX+1, bY);
    create_block[2] = GPoint(bX+1, bY+1);
    create_block[3] = GPoint(bX+2, bY+1);
  }
  else if (type == T) {
    create_block[0] = GPoint(bX, bY);
    create_block[1] = GPoint(bX-1, bY+1);
    create_block[2] = GPoint(bX, bY+1);
    create_block[3] = GPoint(bX+1, bY+1);
  }
}

// Rotate the current block.
// Yeah, I had to map these out on paper.
void rotate_block (GPoint *new_block, GPoint *old_block, int block_type, int rotation) {
  if (block_type == SQUARE) {
    // Haha, yeah no.
  }
  else if (block_type == LINE) {
    if (rotation == 0) {
      new_block[0] = GPoint(old_block[2].x, old_block[0].y-1);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[0].y+1);
      new_block[3] = GPoint(old_block[2].x, old_block[0].y+2);
    }
    else if (rotation == 1) {
      new_block[0] = GPoint(old_block[0].x+1, old_block[2].y);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[0].x-1, old_block[2].y);
      new_block[3] = GPoint(old_block[0].x-2, old_block[2].y);
    }
    else if (rotation == 2) {
      new_block[0] = GPoint(old_block[2].x, old_block[0].y+1);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[0].y-1);
      new_block[3] = GPoint(old_block[2].x, old_block[0].y-2);
    }
    else if (rotation == 3) {
      new_block[0] = GPoint(old_block[0].x-1, old_block[2].y);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[0].x+1, old_block[2].y);
      new_block[3] = GPoint(old_block[0].x+2, old_block[2].y);
    }
  }
  else if (block_type == J) {
    if (rotation == 0) {
      new_block[0] = GPoint(old_block[3].x, old_block[0].y);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[1].y);
      new_block[3] = GPoint(old_block[2].x, old_block[1].y+1);
    }
    else if (rotation == 1) {
      new_block[0] = GPoint(old_block[0].x, old_block[3].y);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x-1, old_block[2].y);
    }
    else if (rotation == 2) {
      new_block[0] = GPoint(old_block[3].x, old_block[0].y);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[1].y);
      new_block[3] = GPoint(old_block[2].x, old_block[1].y-1);
    }
    else if (rotation == 3) {
      new_block[0] = GPoint(old_block[0].x, old_block[3].y);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x+1, old_block[2].y);
    }
  }
  else if (block_type == L) {
    if (rotation == 0) {
      new_block[0] = GPoint(old_block[1].x, old_block[1].y+1);
      new_block[1] = GPoint(old_block[2].x, old_block[1].y+1);
      new_block[2] = GPoint(old_block[2].x, old_block[1].y);
      new_block[3] = GPoint(old_block[2].x, old_block[1].y-1);
    }
    else if (rotation == 1) {
      new_block[0] = GPoint(old_block[1].x-1, old_block[1].y);
      new_block[1] = GPoint(old_block[1].x-1, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[0].x, old_block[2].y);
    }
    else if (rotation == 2) {
      new_block[0] = GPoint(old_block[1].x, old_block[1].y-1);
      new_block[1] = GPoint(old_block[2].x, old_block[1].y-1);
      new_block[2] = GPoint(old_block[2].x, old_block[1].y);
      new_block[3] = GPoint(old_block[2].x, old_block[1].y+1);
    }
    else if (rotation == 3) {
      new_block[0] = GPoint(old_block[1].x+1, old_block[1].y);
      new_block[1] = GPoint(old_block[1].x+1, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[0].x, old_block[2].y);
    }
  }
  else if (block_type == S) {
    if (rotation == 0) {
      new_block[0] = GPoint(old_block[0].x, old_block[2].y+1);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x, old_block[0].y);
    }
    else if (rotation == 1) {
      new_block[0] = GPoint(old_block[2].x-1, old_block[0].y);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x, old_block[1].y);
    }
    else if (rotation == 2) {
      new_block[0] = GPoint(old_block[0].x, old_block[2].y-1);
      new_block[1] = GPoint(old_block[0].x, old_block[2].y);
      new_block[2] = GPoint(old_block[1].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x, old_block[0].y);
    }
    else if (rotation == 3) {
      new_block[0] = GPoint(old_block[2].x+1, old_block[0].y);
      new_block[1] = GPoint(old_block[2].x, old_block[0].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[1].x, old_block[1].y);
    }
  }
  else if (block_type == Z) {
    if (rotation == 0) {
      new_block[0] = GPoint(old_block[3].x, old_block[0].y);
      new_block[1] = GPoint(old_block[3].x, old_block[2].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[2].x, old_block[2].y+1);
    }
    else if (rotation == 1) {
      new_block[0] = GPoint(old_block[0].x, old_block[3].y);
      new_block[1] = GPoint(old_block[3].x, old_block[3].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[2].x-1, old_block[2].y);
    }
    else if (rotation == 2) {
      new_block[0] = GPoint(old_block[3].x, old_block[0].y);
      new_block[1] = GPoint(old_block[3].x, old_block[2].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[2].x, old_block[2].y-1);
    }
    else if (rotation == 3) {
      new_block[0] = GPoint(old_block[0].x, old_block[3].y);
      new_block[1] = GPoint(old_block[3].x, old_block[3].y);
      new_block[2] = GPoint(old_block[2].x, old_block[2].y);
      new_block[3] = GPoint(old_block[2].x+1, old_block[2].y);
    }
  }
  else if (block_type == T) {
    if (rotation == 0) {
      new_block[0] = old_block[3];
      new_block[1] = old_block[0];
      new_block[2] = old_block[2];
      new_block[3] = GPoint(old_block[0].x, old_block[2].y+1);
    }
    else if (rotation == 1) {
      new_block[0] = old_block[3];
      new_block[1] = old_block[0];
      new_block[2] = old_block[2];
      new_block[3] = GPoint(old_block[2].x-1, old_block[2].y);
    }
    else if (rotation == 2) {
      new_block[0] = old_block[3];
      new_block[1] = old_block[0];
      new_block[2] = old_block[2];
      new_block[3] = GPoint(old_block[0].x, old_block[2].y-1);
    }
    else if (rotation == 3) {
      new_block[0] = old_block[3];
      new_block[1] = old_block[0];
      new_block[2] = old_block[2];
      new_block[3] = GPoint(old_block[2].x+1, old_block[2].y);
    }
  }
}

int find_max_drop (GPoint *block, uint8_t grid[10][20]) {
  bool canDrop = true;
  int drop_amount = 0;
  while (canDrop) {
    for (int i=0; i<4; i++) {
      int benthic = block[i].y + 1 + drop_amount;
      if (benthic > 19) { canDrop = false; }
      if (grid[block[i].x][benthic]) { canDrop = false; }
    }
    if (canDrop) {
      drop_amount += 1;
    }
  }
  return drop_amount;
}

// Just to make the 'next block' display nice and centered.
int next_block_offset (int block_type) {
  if (block_type == T) { return 0; }
  else if (block_type == SQUARE) { return -4; }
  else if (block_type == S || block_type == L) { return 8; }
  else if (block_type == Z || block_type == J) { return -8; }
  else { return -12; }
}
