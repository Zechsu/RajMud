#include <globals.h>

inherit CLEAN_UP;
inherit M_OPEN;
inherit M_LOCK;

int is_opened = 0;

int add_side(string side, string destination, string other_side, object room) {
    if (!room) {
        room = previous_object();
    }

    room->add_door(side, this_object(), destination);

    if (other_side) {
        destination->add_door(other_side, this_object(), room);
    }
    
    return 1;
}

int is_door() {
    return 1;
}