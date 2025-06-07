#include <lib.h>

inherit LIB_ROOM;

void create() {
    set_short("Cave");
    set_long("The cave is dimly lit, cool and damp. Surrounded by rough stone walls, glimmering stalactites and stalagmites. The water drips down on the uneven pebbled ground.");
    add_exit("north", "/domains/goblincave/rooms/gc_2");

    add_item("/domains/goblincave/mobiles/goblin_spearman");
}