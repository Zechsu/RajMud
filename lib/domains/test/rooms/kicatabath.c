#include <lib.h>

inherit LIB_ROOM;

int opened = 0;

void create() {
    ::create();
    set_short("Kicata Toilets");
    set_long("Ew shit stain on the wall. Big sink in the middle.");
    add_exit("west", "/domains/test/rooms/inkicata");
    add_prop("sink", "Maybe you should try pushing it.");
    add_item("/domains/test/items/raciststone");
}

void init() {
    add_action("do_push", "push");
}

int do_push(string str) {
    if (!str || trim(str) == "") {
        return 0;
    }
    if (str == "sink" || str == "the sink") {
        if (!opened) {
            object door = new(LIB_DOOR);
            tell_room(this_object(), "A secret path opens!\n");
            door->set_short("secret path");
            door->add_side("in", "/domains/test/rooms/chamber", "out");
            door->toggle_opened();
            door->set_can_open(0);
            door->set_can_close(0);
            opened = 1;
            return 1;
        }
        else {
            write("The sink is already pushed in.\n");
            return 1;
        }
        return 0;
    }
}
