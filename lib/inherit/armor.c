#include <lib.h>

inherit LIB_ITEM;
inherit LIB_WORN;

void hook_state(string tag, function hook, int state);
private nosave function move_hook = (: event_remove, 1 :);

void create() {
    ::create();
    set_wear_mess("You put on $I in $L.");
    set_remove_mess("You remove $I.");
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

varargs mixed event_wear(object who, string* limbs) {
    hook_state("move", move_hook, this_player() && this_player() != this_object());
    return ::event_wear(who, limbs);
}