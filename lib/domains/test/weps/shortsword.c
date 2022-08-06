#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("shortsword");
    set_long("A shortsword for testing, obviously");
    set_ids(({"shortsword", "sword"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
    set_attacks(({"slash"}));
}

int event_strike(object target) {
    return 36;
}

string query_attack_message() {
    return "$N $vswing at $T";
}