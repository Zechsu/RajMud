#include <lib.h>

inherit "/std/obj/limb";

void create(string race) {
    ::create(race);
    set_short("severed " + race + " hand");
    set_long("Remains of a " + race + " hand.");
    set_ids(({"limb", "hand", race + " hand"}));
    set_adjectives(({"severed"}));
    set_butcher(({race + " meat"}));
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
}