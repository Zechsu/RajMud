#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Inside sshapkata");
    set_long("How the fuck did we get in here?");
    add_exit("north", "/domains/test/rooms/bedechka");
}
