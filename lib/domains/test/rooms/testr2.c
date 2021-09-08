#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room 2");
    set_long("Second room in the game, wooo!");
}
