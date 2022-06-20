#include <lib.h>
#include <modules.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Forest entrance");
    set_long("Enter if you dare.");
    add_exit("in", "forest/0,0");
}
