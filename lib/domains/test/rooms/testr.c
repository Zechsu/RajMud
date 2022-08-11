#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room for test purposes");
    set_long("Testing room 1");
    add_exit("north", "/domains/test/rooms/testr2");
    add_exit("up", "/domains/test/rooms/testrup");
    add_exit("east", "/domains/test/rooms/forest_entrance");
    add_item("/domains/test/items/dispenser");
}
