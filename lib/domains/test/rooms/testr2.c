#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room 2");
    set_long("Second room wooo");
    add_exit("south", "/domains/test/rooms/testr");
    add_exit("east", "/domains/test/rooms/kicata");
}
