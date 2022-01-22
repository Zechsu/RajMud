#include <lib.h>

inherit LIB_ITEM;
inherit LIB_WORN;

void hook_state(string tag, function hook, int state);
private nosave function move_hook = (: event_remove, 1 :);


void create() {
    ::create();
    set_wear_mess("You wield $I in $L.");
    set_remove_mess("You unwield $I.");
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

    if (sz == 1) {
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

varargs mixed event_wear(object who, string* limbs) {
    hook_state("move", move_hook, this_player() && this_player() != this_object());
    return ::event_wear(who, limbs);
}