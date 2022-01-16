#include <lib.h>
#include <modules.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("shortsword");
    set_long("A shortsword for testing, obviously");
    set_ids(({"shortsword", "sword"}));
    set_required_limbs(({"hand"}));
    set_handed(1);
}