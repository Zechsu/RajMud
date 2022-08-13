#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("wooden spear");
    set_long("A long wooden stick with a pointy stone attached at the end of it.");
    set_ids(({"wooden spear", "spear"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_SPEAR);
}