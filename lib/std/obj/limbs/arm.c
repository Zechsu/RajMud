#include <lib.h>

inherit "/std/obj/limb";

void create(string race) {
    ::create(race);
    set_short("severed " + race + " arm");
    set_long("Remains of a " + race + " arm.");
    set_ids(({"limb", "arm", race + " arm"}));
    set_adjectives(({"severed"}));
    set_butcher(({race + " meat"}));
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
}