#include <lib.h>
#include <daemons.h>
#include "include/weapon.h"

inherit LIB_ITEM;

private string* valid_limbs;
// string since wielded on a specific limb
private string wielded;

void create() {
    ::create();
    add_save(({"wielded"}));
}

int can_wield(object who, string limb) {
    if (member_array(limb, valid_limbs) == -1) {
        return notify_fail(sprintf("You can't wield that in %s.\n", limb));
    }
    if (!member_array(limb, this_player()->query_limbs())) {
        return notify_fail("You're missing the limb.\n");
    }
    return 1;
}

int can_unwield(object who) {
    if (!wielded) {
        return notify_fail("You're not wielding that.\n");
    }
    return 1;
}

varargs mixed event_wield(object who, string limb) {
    if (!who) {
        who = this_player();
    }
    if (!limb) {
        limb = element_of(valid_limbs);
    }
    if (!can_wield(who, limb)) {
        return 0;
    }
    write("You wield " + query_short() + ".\n");
    say(sprintf("%s wields %s.\n", this_player()->query_name(), query_short()));
    wielded = limb;
    return 1;
}

varargs event_unwield(object who) {
    if (!who) {
        who = this_player();
    }
    if (!can_unwield()) {
        return 0;
    }
    write("You unwield " + query_short() + ".\n");
    say(sprintf("%s unwields %s.\n", this_player()->query_name(), query_short()));
    wielded = 0;
    return 1;
}

varargs mixed event_drop(object who) {
    if (!who) {
        who = this_player();
    }
    if (wielded) {
        event_unwield(who);
    }
    return item::event_drop(who);
}

void set_valid_limbs(mixed equips) {
    if (!stringp(equips) && !arrayp(equips)) {
        Log("debug", sprintf("Item received wrong equipment slots type: %O, expected string|string*", equips));
    }
    valid_limbs = equips;
}

string* query_valid_limbs() {
    return valid_limbs;
}

int is_weapon() {
    return 1;
}

string query_wielded() {
    return wielded;
}