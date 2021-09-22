#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Kicata Toilets");
    set_long("Ew shit stain on the wall. Big sink in the middle.");
    add_exit("west", "/domains/test/rooms/inkicata");
    add_prop("sink", "Maybe you should try pushing it.");
}

void init() {
    add_action("do_push", "push");
}

int do_push(string str) {
    if (!str || trim(str) == "") {
        return 0;
    }
    if (str == "sink" || str == "the sink") {
        tell_object(this_player(), "A secret path opens.\n");
        add_exit("in", "/domains/test/rooms/chamber");
        return 1;
    }
    return 0;
}