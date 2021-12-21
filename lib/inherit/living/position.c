#include <globals.h>
#include "include/position.h"

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

string query_position_string() {
    switch (position) {
        case STANDING:
            return sprintf("%s is standing here.", query_name());
        case FLYING:
            return sprintf("%s is flying here.", query_name());
        case SITTING:
            return sprintf("%s is sitting here.", query_name());
        default:
            return sprintf("%s is here.", query_name());
    }
    return 0;
}
