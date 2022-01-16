#include <lib.h>

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
    return layer;
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

    if(!limbs) limbs = required_limbs;
    if (worn) {
        return notify_fail("You alredy have it on.\n");
    }

    free_limbs = who->find_limbs(limbs, 1);
    if (sizeof(free_limbs) < sizeof(required_limbs)) {
        return notify_fail("You miss the limbs.\n");
    }
    foreach (string limb in free_limbs) {
        foreach(object worn in player_body[limb]["worn"]) {
            if (worn->query_layer() == layer) {
                free_limbs -= ({limb});
            }
        }
    }
    if (!sizeof(free_limbs)) {
        return notify_fail("You have nowhere to put this on.\n");
    }

    return free_limbs;
}

varargs mixed event_wear(object who, string* limbs) {
    string* wear;
    mapping player_body;
    string mess = wear_mess;
    if (!who) who = this_player();
    if (!limbs) limbs = required_limbs;

    wear = can_wear(who, limbs);
    if (!sizeof(wear)) return 0;

    player_body = who->query_body();
    foreach(string limb in wear) {
        player_body[limb]["worn"] += ({this_object()});
    }
    worn = wear;

    mess = replace_string(mess, "$I", this_object()->query_short());
    mess = replace_string(mess, "$L", list_strings(worn));
    write(mess + "\n");

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
        string mess = replace_string(remove_mess, "$I", this_object()->query_short());
        write(mess + "\n");
    }

    return 1;
}