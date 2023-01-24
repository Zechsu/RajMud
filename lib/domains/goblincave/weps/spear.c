#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("wooden spear");
    set_long("A crudely made weapon constisting of a shaprened stone attached to a wooden shaft. The stone is chipped and uneven, and the wood, rough and splintered.");
    set_ids(({"wooden spear", "spear"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_SPEAR);
}
