#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Kicata Hall");
    set_long("Whats the kica doing");
    add_exit("out", "/domains/test/rooms/kicata");
    add_exit("east", "/domains/test/rooms/kicatabath");
}