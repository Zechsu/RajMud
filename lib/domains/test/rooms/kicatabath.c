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
            add_door("a secret tunnel", "in", __DIR__ + "chamber", 1);
            query_door("in")->set_can_close(0);
            query_door("in")->set_can_open(0);
            query_door("in")->toggle_opened();
            write("A secret tunnel opens!\n");
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
