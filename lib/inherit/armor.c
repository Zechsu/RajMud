#include <lib.h>

inherit LIB_ITEM;
inherit LIB_WORN;

void hook_state(string tag, function hook, int state);
private nosave function move_hook = (: event_remove, 1 :);

void create() {
    ::create();
    set_wear_mess("$N $vput on $t in $L.");
    set_remove_mess("$N $vremove $t.");
}

// Check if object can be wielded
int is_wearable() {
    return 1;
}

string worn_attributes() {
    if (query_worn()) {
        string ret = "worn in ";
        ret += list_strings(query_worn());
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}

varargs int event_wear(object who, string* limbs) {
    int res = ::event_wear(who, limbs);

    if (res)
        hook_state("move", move_hook, this_player() && this_player() != this_object());

    return res;
}
