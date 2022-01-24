#include <modules.h>
#include <lib.h>

inherit LIB_ARMOR;

void create() {
    ::create();
    set_short("plain shirt");
    set_long("It's a plain shirt for testing purposes.");
    set_ids(({"shirt", "plain shirt"}));
    set_required_limbs(({"torso"}));
}