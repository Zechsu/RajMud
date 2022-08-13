#include <lib.h>
#include <armor_layers.h>
#include <weapon_types.h>
#include <daemons.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("slingshot");
    set_long("A thick piece of wood split in the middle, forming a Y-shape.");
    set_ids(({"slingshot"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_weapon_type(WEAPON_SLINGSHOT);
}