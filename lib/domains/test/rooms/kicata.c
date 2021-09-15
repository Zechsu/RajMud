#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Kicata ???");
    set_long("Whats the kica doing");
    add_exit("west", "/domains/test/rooms/testr2");
}