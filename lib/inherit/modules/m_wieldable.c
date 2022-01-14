#include <lib.h>
#include <armor_layers.h>

// Prototype functions
void add_hook(string tag, function hook);
void hook_state(string tag, function hook, int state);
int unwield_me(int quietly);
varargs mixed event_unwield(int quietly);

// requires limbs to wield
private string* required_limbs;
// optional limbs
private string* optional_limbs;
// if wielded on which limbs is it wielded
private string* wielded;
private nosave function move_hook = (: event_unwield, 1 :);
// is it 1-handed or 2-handed weapon
private int handed = 1;
// always worn on the weapon layer
private int layer = A_WEAPON;

// Check if object can be wielded
int is_wieldable() {
    return 1;
}

// Check if it's wielded
int is_wielded() {
    return wielded? 1 : 0;
}

string* query_worn() {
    return wielded;
}

void set_required_limbs(string* limbs) {
    required_limbs = limbs;
}

void set_handed(int h) {
    handed = h;
}

string* query_required_limbs() {
    return required_limbs;
}

mixed can_wield(object who, string limb) {
    string* hands = Race(this_player()->query_race())->query_hands();
    mapping player_body = this_player()->query_body();

    if (wielded) {
        return notify_fail("You're already wielding it.\n");
    }

    // Find each limb with "hand" in the name
    hands = this_player()->find_limbs(limb, 1);
    
    // If we have no hands
    if (!sizeof(hands)) {
        return notify_fail("You do not have hands.\n");
    }
    // Get all the free hands
    foreach(string hand in hands) {
        foreach (object worn in player_body[hand]["worn"]) {
            if (worn->query_layer() == A_WEAPON) {
                hands -= ({hand});
            }
        }
    }

    // Check if we have enough hands free for 2-handed weapons
    // TODO: Make it return all the hands, then we get 2 random hands for 2h or 1 random for 1h weapons
    // Make handedness? trait. If player's right handed just return right hand altho that wouldn't always work I guess
    // Maybe make it inside the human race file. It'll check for handedness and return correct hand
    if (sizeof(hands) >= handed) {
        return element_of(hands);
    }
    else {
        return notify_fail("You do not have a free hand.\n");
    }
}

varargs mixed event_wield(object who, string* limbs) {
    mapping player_body;
    string hand;
    if (!who) who = this_player();
    if (!limbs) limbs = required_limbs;

    foreach (string limb in limbs) {
        hand = can_wield(who, limb);
        if (!hand) return;
    }

    player_body = this_player()->query_body();
    player_body[hand]["worn"] += ({this_object()});
    wielded = ({hand});

    write(sprintf("You wield %s in %s\n", this_object()->query_short(), hand));

    hook_state("move", move_hook, this_player() && this_player() != this_object());
    return 1;
}

int unwield_me(int quietly) {
    mapping player_body = this_player()->query_body();
    object to = this_object();
    foreach (string str in wielded) {
        player_body[str]["worn"] -= ({this_object()});
        // int sz = sizeof(player_body[str]["worn"]);
        // for (int i = 0; i < sz; i++) {
        //     if (player_body[str]["worn"][i] == to) {
        //         player_body[str]["worn"] -= to;
        //     }
        // }
    }
    wielded = 0;
    if (!quietly) {
        write("You unwield " + to->query_short() + ".\n");
    }
    return 1;
}

varargs mixed event_unwield(int quietly) {
    if (!wielded) {
        return notify_fail("You're not wielding that.\n");
    }

    return unwield_me(quietly);
}

string worn_attributes() {
    if (wielded) {
        string ret = "wielded in ";
        ret += list_strings(wielded);
        return "%^GREEN%^" + sprintf(" (%s) ", ret) + "%^RESET%^";
    }
    return "";
}

int query_layer() {
    return A_WEAPON;
}