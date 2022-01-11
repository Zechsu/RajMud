#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_DECAY;

void create() {
    ::create();
    set_short("severed limb");
    set_long("Remains of a limb");
    set_ids(({"limb"}));
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
}