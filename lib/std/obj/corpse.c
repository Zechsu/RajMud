#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_DECAY;

void create() {
    ::create();
    if (!query_short()) {
        set_short("corpse");
    }
    if (!query_long()) {
        set_long("The corpse of someone.");
    }
    if (!sizeof(query_ids())) {
        set_ids(({"corpse"}));
    }
    add_save(({"short_desc", "long_desc", "ids"}));
}
