#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("shortsword");
    set_long("A shortsword for testing, obviously");
    set_ids(({"shortsword", "sword"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_SWORD);
}

int event_strike(object target) {
    return Weapon_Type(WEAPON_SWORD)->calculate_damage_rating(this_interactive()) / 10;
}