#include <globals.h>

inherit CLEAN_UP;

int is_opened = 0;

int add_side(string side, string destination, string other_side, object room) {
    if (!room) {
        room = previous_object();
    }
    room->add_door(side, this_object(), destination);
    destination->add_door(other_side, this_object(), room);
    return 1;
}

int is_open() {
    return is_opened;
}

void toggle_opened() {
    is_opened = !is_opened;
}

int open() {
    if (is_opened == 0) {
        is_opened = 1;
        return 1;
    }
    else {
        return 0;
    }
}

int close() {
    is_opened = 0;
    return 1;
}