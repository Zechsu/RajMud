#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Air room");
    set_long("Above");
    add_exit("down", "/domains/test/rooms/testr");
}
