#include <lib.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("shortsword");
    set_long("Short but sturdy weapon.");
    set_ids(({"shortsword", "sword"}));
    set_valid_limbs(({"right hand", "left hand"}));
}