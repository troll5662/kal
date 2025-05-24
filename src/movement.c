#include "definitions.h"
#include "movement.h"

void move_up(struct cursor_t *cursor) {
    if (cursor->y > 0)   cursor->y--;
    else                return;

    if (cursor->y == OPTIONS1_NUM) {
        if      (cursor->x == 1) cursor->x = 2;
        else if (cursor->x == 2) cursor->x = 4;
    } else {
        cursor->x = 0;
    }
}

void move_down(struct cursor_t *cursor) {
    if (cursor->y < 4)   cursor->y++;
    else                return;

    if (cursor->y == OPTIONS2_NUM) {
        if      (cursor->x == 1)                     cursor->x = 0;
        else if (cursor->x == 2)                     cursor->x = 1;
        else if (cursor->x == 3 || cursor->x == 4)    cursor->x = 2;
    } else {
        cursor->x = 0;
    }
}

void move_left(struct cursor_t *cursor) {
    if (cursor->y == OPTIONS1_NUM || cursor->y == OPTIONS2_NUM) {
        if (cursor->x > 0)   cursor->x--;
    } else {
        return;
    }
}

void move_right(struct cursor_t *cursor) {
    if (cursor->y == OPTIONS1_NUM) {
        if (cursor->x < 4) cursor->x++;
    } else if (cursor->y == OPTIONS2_NUM) {
        if (cursor->x < 2) cursor->x++;
    } else {
        return;
    }
}