#include <modules.h>
#include <lib.h>

inherit LIB_ITEM;
inherit M_WEARABLE;

void create() {
    ::create();
    set_short("plain shirt");
    set_long("It's a plain shirt for testing purposes.");
    set_ids(({"shirt", "plain shirt"}));
    set_required_limbs(({"torso"}));
}