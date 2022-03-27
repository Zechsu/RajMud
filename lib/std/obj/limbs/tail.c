#include <lib.h>

inherit "/std/obj/limb";

void create(string race) {
    ::create(race);
    set_short("severed " + race + " tail");
    set_long("Remains of a " + race + " tail.");
    set_ids(({"limb", "tail", race + " tail"}));
    set_adjectives(({"severed"}));
    set_butcher(({race + " meat"}));
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
}