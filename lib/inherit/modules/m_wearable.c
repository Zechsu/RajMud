#include <lib.h>
#include <armor_layers.h>

// Prototypes and forward declares
void hook_state(string tag, function hook, int state);
varargs mixed event_remove(int quietly);

private string* required_limbs;
private string* optional_limbs;
private int layer;
// if it's worn on which limbs is it
private string* worn;
private nosave function move_hook = (: event_remove, 1 :);

int is_wearable() {
    return 1;
}

void set_layer(int l) {
    layer = l;
}

int query_layer() {
    return layer;
}

int is_worn() {
    return worn? 1 : 0;
}

void set_required_limbs(string* limbs) {
    required_limbs = limbs;
}

mixed can_wear(object who, string* where) {
    mapping player_body = this_player()->query_body();
    string* limbs = this_player()->find_limbs(where, 1);
    if (sizeof(limbs) < sizeof(required_limbs)) {
        return notify_fail("You do not have the limbs.\n");
    }
    if (worn) {
        return notify_fail("You're already wearing it.\n");
    }

    foreach (string limb in limbs) {
        foreach(object worn in player_body[limb]["worn"]) {
            if (worn->query_layer() == layer) {
                return notify_fail("You're already wearing something.\n");
            }
        }
    }

    return limbs;
}

varargs mixed event_wear(object who, string* limbs, int quietly) {
    string* wear;
    mapping player_body;
    if (!who) who = this_player();
    if (!limbs) limbs = required_limbs;

    wear = can_wear(who, limbs);
    if (!wear) {
        return 0;
    }

    player_body = who->query_body();
    foreach(string limb in wear) {
        player_body[limb]["worn"] += ({this_object()});
    }
    worn = wear;

    write("You put on " + this_object()->query_short() + ".\n");

    hook_state("move", move_hook, this_player() && this_player() != this_object());
    return 1;
}

int remove_me(int quietly) {
    object to = this_object();
    mapping player_body = this_player()->query_body();
    foreach (string str in worn) {
        player_body[str]["worn"] -= ({to});
    }
    worn = 0;
    if (!quietly) {
        write("You remove " + to->query_short() + ".\n");
    }
    return 1;
}

varargs mixed event_remove(int quietly) {
    if (!worn) {
        return notify_fail("You're not wearing that.\n");
    }

    return remove_me(quietly);
}

string worn_attributes() {
    if (worn) {
        string ret = "worn on ";
        ret += list_strings(worn);
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}