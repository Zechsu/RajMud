#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

void create() {
    ::create();
    set_short("sandals");
    set_long("Sandals for testing, obviously");
    set_ids(({"sandals"}));
}

int is_wearable() {
    return 1;
}

varargs mixed event_wear(object who, string* limbs) {
    string* wear;
    mapping player_body;
    string mess;
    string verb = query_verb();
    if (!who) who = this_player();

    if (query_worn()) {
        return notify_fail("You already have them on.\n");
    }
    if (verb == "wear") {
        set_required_limbs(({"leg", "leg"}));
        set_layer(A_SHOE);
        set_wear_mess("You put on $I in $L.");
        set_remove_mess("You take off $I.");
    }
    else if (verb == "wield") {
        set_required_limbs(({"hand", "hand"}));
        set_layer(A_WEAPON);
        set_wear_mess("You wield $I in $L.");
        set_remove_mess("You unwield $I.");
    }

    if (!limbs) limbs = query_required_limbs();

    wear = can_wear(who, limbs);
    if (!sizeof(wear)) return 0;

    player_body = who->query_body();
    foreach(string limb in wear) {
        player_body[limb]["worn"] += ({this_object()});
    }
    set_worn(wear);

    mess = query_wear_mess();
    mess = replace_string(mess, "$I", this_object()->query_short());
    mess = replace_string(mess, "$L", list_strings(query_worn()));
    write(mess + "\n");

    hook_state("move", (:event_remove, 1:), this_player() && this_player() != this_object());

    return 1;
}

string worn_attributes() {
    if (query_worn()) {
        string ret = query_layer() == A_WEAPON? "wielded in " : "worn in ";
        ret += list_strings(query_worn());
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}