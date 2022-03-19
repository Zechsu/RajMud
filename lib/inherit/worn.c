#include <lib.h>
#include <armor_layers.h>

// Prototype functions
string query_short();

// requires limbs to wield
private string* required_limbs;
// optional limbs
private string* optional_limbs;
private int layer;
// if it's worn on which limbs is it
private string* worn;
// Message written out when object is equipped
private string wear_mess;
// Message written out when object is unequipped
private string remove_mess;

varargs mixed query_real_limbs(string* args, int slot);

string* query_worn() {
    return worn;
}

void set_worn(string* where) {
    worn = where;
}

int is_worn() {
    return worn? 1 : 0;
}

string* query_required_limbs() {
    return required_limbs;
}

void set_required_limbs(string* limbs) {
    required_limbs = limbs;
}

int query_layer() {
    if (layer != -1) {
        return layer;
    }
    return -1;
}

void set_layer(int l) {
    layer = l;
}

string query_wear_mess() {
    return wear_mess;
}

void set_wear_mess(string mess) {
    wear_mess = mess;
}

string query_remove_mess() {
    return remove_mess;
}

void set_remove_mess(string mess) {
    remove_mess = mess;
}

mixed can_wear(object who, string* limbs) {
    string* free_limbs;
    mapping player_body = this_player()->query_body();
    int size;

    if(!limbs) limbs = required_limbs;
    if (worn) {
        return notify_fail("You alredy have it on.\n");
    }

    if (!who->has_limbs(limbs)) {
        return notify_fail("You miss the limbs.\n");
    }

    free_limbs = query_real_limbs(limbs, layer);

    if (sizeof(free_limbs) < sizeof(required_limbs)) {
        return notify_fail("You have nowhere to put this on.\n");
    }

    return free_limbs;
}

varargs mixed event_wear(object who, string* limbs) {
    string* wear, *composed;
    mapping player_body;
    string mess;
    if (!who) who = this_player();
    if (!limbs) limbs = required_limbs;

    wear = can_wear(who, limbs);
    if (sizeof(wear) == 0)
        return notify_fail("You cannot do that!\n");

    player_body = who->query_body();
    foreach(string limb in wear) {
        player_body[limb]["worn"] += ({this_object()});
    }
    worn = wear;

    mess = wear_mess;
    mess = replace_string(mess, "$L", list_strings(worn));
    composed = compose_message(this_interactive(), mess, this_object());

    tell_object(this_interactive(), capitalize(composed[0]) + "\n");
    tell_room(environment(this_interactive()), composed[2] + "\n", ({this_interactive()}));

    return 1;
}

varargs mixed event_remove(int quietly) {
    object to;
    mapping player_body;

    if (!worn) {
        return notify_fail("You do not have that on.\n");
    }

    to = this_object();
    player_body = this_player()->query_body();

    foreach (string str in worn) {
        player_body[str]["worn"] -= ({to});
    }

    worn = 0;

    if (!quietly) {
        string* mess = compose_message(this_interactive(), remove_mess, this_object());
        tell_object(this_interactive(), capitalize(mess[0]) + "\n");
        tell_room(environment(this_interactive()), mess[2] + "\n", ({this_interactive()}));
    }

    return 1;
}

void remove_worn(string limb) {
    mapping player_body = this_player()->query_body();
    worn -= ({limb});
    player_body[limb]["worn"] -= ({this_object()});
}

varargs mixed query_real_limbs(string* args, int slot) {
    object tp = this_player();
    // List of all limbs we will need (not severed)
    string* limbs = this_player()->find_limb(args, 1);
    string* ret = ({});

    if (slot) {
        foreach (string r in limbs) {
            if (sizeof(tp->query_worn(r, layer))) {
                limbs -= ({r});
            }
        }
   }

    foreach (string req in required_limbs) {
        for (int i = 0; i < sizeof(limbs); i++) {
            if (strsrch(limbs[i], req) > -1) {
                ret += ({limbs[i]});
                limbs -= ({limbs[i]});
                break;
            }
        }
    }

    return ret;
}
