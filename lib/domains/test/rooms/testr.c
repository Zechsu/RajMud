#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room for test purposes");
    set_long("Testing room 1");
    add_exit("north", "/domains/test/rooms/testr2");
}
