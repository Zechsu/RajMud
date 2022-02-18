#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("30cm bbc dildo");
    set_long("It appears to be the smallest size Kocinofs collection has to offer.");
    set_ids(({"dildo", "bbc", "bbc dildo", "30cm bbc dildo"}));
    set_required_limbs(({"hand"}));
    set_layer(A_WEAPON);
}

int event_strike(object target) {
    return 2;
}

string query_attack_message() {
    return "$N $vbash $T in the $L with $o";
}