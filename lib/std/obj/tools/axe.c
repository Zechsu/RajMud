#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("lumbering axe");
    set_long("It's an lumbering axe. Use it to cut trees.");
    set_ids(({"axe", "lumbering", "lumbering axe"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
}

int is_lumbering_tool() {
    return 1;
}

int event_strike(object target) {
    return 1;
}

string query_attack_message() {
    return "$N $vswing at $T";
}