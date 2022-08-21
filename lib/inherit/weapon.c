#include <lib.h>
#include <daemons.h>
#include "include/weapon.h"

inherit LIB_WORN;

void hook_state(string tag, function hook, int state);
private nosave function move_hook = (: event_remove, 1 :);
private int weapon_class = 1;
private string* attacks;
private int weapon_type;

void create() {
    worn::create();
    set_wear_mess("$N $vwield $t in $p $L.");
    set_remove_mess("$N $vunwield $p $t.");
}

// Check if object can be wielded
int is_wieldable() {
    return 1;
}

string worn_attributes() {
    if (query_worn()) {
        string ret = "wielded in ";
        ret += list_strings(query_worn());
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}

mixed can_wear(object who, string* limbs) {
    mixed res = ::can_wear(who, limbs);
    int sz = sizeof(res);

    if (!res) {
        return 0;
    }

    if (sz != 1) {
        string handedness = this_player()->query_trait("handedness");
        foreach (string str in res) {
            if (strsrch(str, handedness) != -1) {
                return ({str});
            }
        }
    }
    else {
        return res;
    }
}

varargs int event_wear(object who, string* limbs) {
    int res = ::event_wear(who, limbs);

    if (res)
        hook_state("move", move_hook, this_player() && this_player() != this_object());

    return res;
}

void set_attacks(string* new_attacks) {
    attacks = map(new_attacks, (: $1 :));
}

string* query_attacks() {
    return copy(attacks);
}

void set_class(int c) {
    weapon_class = c;
}

int query_class() {
  return weapon_class;
}

// Called each time weapon hits an enemy
int event_strike(object target) {
    return weapon_class;
}

void set_weapon_type(int type) {
    weapon_type = type;
    set_attacks(WEAPON_TYPES_D->query_weapon_type(type)->query_attacks());
}