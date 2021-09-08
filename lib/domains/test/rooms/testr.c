#include <globals.h>
#include <def.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room for test purposes");
    set_long("This room is strictly only for testing!\nAny non test activities will defy the room name and thus lead to a paradox!");
    add_exit("north", AREAPATH+"testr2");
}
