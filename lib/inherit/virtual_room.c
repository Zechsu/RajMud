#include <lib.h>

inherit LIB_ROOM;

int x, y;
int max_x, max_y;
int max_neg_x, max_neg_y;

int query_max_x() {
    return max_x;
}

void set_square_max_area(int _x, int _y) {
    max_x = _x;
    max_y = _y;
    max_neg_x = -_x;
    max_neg_y = -_y;
}

void set_x(int _x) {
    x = _x;
}

void set_y(int _y) {
    y = _y;
}

void create() {
    ::create();
}