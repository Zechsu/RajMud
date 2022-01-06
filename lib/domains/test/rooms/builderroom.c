#include <globals.h>

inherit LIB_ROOM;

void create() {
    set_short("Raboti");
    set_long("Nice raboti");
    add_exit("west", __DIR__ + "kicatabath");
}