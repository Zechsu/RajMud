#include <lib.h>

inherit LIB_VIRTUAL_ROOM;

void virtual_create() {
    set_short("In the forest");
    set_long("You're surrounded by all-encompassing greenery.");
    if (x < max_x) {
        set_exit("east", sprintf("/forest/%d,%d", x+1, y));
    }
    if (x > max_neg_x) {
        set_exit("west", sprintf("/forest/%d,%d", x-1, y));
    }
    if (y > max_y) {
        set_exit("north", sprintf("/forest/%d,%d", x, y+1));
    }
    if (y > max_neg_y) {
        set_exit("south", sprintf("/forest/%d,%d", x, y-1));
    }

    if (random(100) > 70) {
        object oak = new("/domains/test/items/oak_tree.c");
        oak->move(this_object());
    }
}