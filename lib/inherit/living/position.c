#include <globals.h>
#include <positions.h>

private int position;

string query_name();

void create() {
    if (!position || position == 0) {
        position = 1;
    }
}

void set_position(int pos) {
    position = pos;
}

int query_position() {
    return position;
}

