#include <lib.h>
#include <armor_layers.h>

inherit LIB_WORN;

void create() {
    set_wear_mess("You wield $I in $L.");
    set_remove_mess("You unwield $I.");
}

// is it 1-handed or 2-handed weapon
private int handed = 1;

// Check if object can be wielded
int is_wieldable() {
    return 1;
}

void set_handed(int h) {
    handed = h;
}

string worn_attributes() {
    if (query_worn()) {
        string ret = "wielded in ";
        ret += list_strings(query_worn());
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}
