#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("broken wooden sword");
    set_long("Once it was a wooden sword, not only the hilt and part of the blade remain.");
    set_ids(({"broken wooden sword", "broken sword", "wooden sword", "sword"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_SWORD);
}