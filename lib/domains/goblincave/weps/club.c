#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("wooden club");
    set_long("A long thick wooden stick formed in the shape of a club.");
    set_ids(({"wooden club", "club"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_CLUB);
}