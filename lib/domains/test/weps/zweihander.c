#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("zweihander");
    set_long("A zweihander for testing, obviously");
    set_ids(({"zweihander", "zwei"}));
    set_required_limbs(({"hand", "hand"}));
    set_layer(A_WEAPON);
}