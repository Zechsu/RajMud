#include <lib.h>

inherit LIB_ITEM;
inherit LIB_WORN;

void hook_state(string tag, function hook, int state);
private nosave function move_hook = (: event_remove, 1 :);
private string* combat_skills;

void create() {
    ::create();
    set_wear_mess("$N $vwield $t in $L.");
    set_remove_mess("$N $vunwield $t.");
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

void set_combat_skills(string* skills) {
    combat_skills = skills;
}

string* query_combat_skills() {
    return combat_skills;
}

string query_attack_mess() {
    return "You hit something.\n";
}