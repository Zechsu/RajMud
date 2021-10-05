#include <globals.h>

#define KABUTO_COLORS       ({"%#6d551d%#", "%#846828%#", "%#907843%#"})
#define SPECIES             ({"Allomyrina dichotoma dichotoma", "Allomyrina dichotoma inchachina", "Allomyrina dichotoma septentrionalis"})

inherit LIB_ITEM;

int health = 10;
int attack = 1;

int idx = secure_random(sizeof(SPECIES));
string col = KABUTO_COLORS[idx];
string specie = SPECIES[idx];

void set_stats();

void create() {
    ::create();
    set_short(col + "kabuto%^RESET%^");
    set_long("A lovely " + col + "kabuto%^RESET%^!");
    set_ids(({"kabuto"}));
    set_stats();
}

void init() {
    add_action("put_in_arena", "put");
}

int put_in_arena(string str) {
    object tp = this_player();

    if (!str) {
        return notify_fail("Put what?\n");
    }

    str = replace_string(str, "the", "");

    if (str == "kabuto in arena") {
        object* inv = environment(tp)->query_items();
        inv = filter_array(inv, (: $1->id("kabuto arena") :));
        if (sizeof(inv) != 0) {
            if (inv[0]->put_kabuto(this_object())) {
                write("You put the " + query_short() + " in the arena.\n");
                return 1;
            }
            else {
                return notify_fail("The arena is full.\n");
            }
        }
        else {
            return notify_fail("There's no arena here.\n");
        }
    }
    else {
        return 0;
    }
}

void set_stats() {
    if (specie == SPECIES[0]) {
        attack += 1;
        health += 2;
        return;
    }
    if (specie == SPECIES[1]) {
        attack += 2;
        return;
    }
    if (specie == SPECIES[2]) {
        health += 2;
        return;
    }
    return;
}

int is_kabuto() {
    return 1;
}

int query_health() {
    return health;
}

int query_attack() {
    return attack;
}

string query_specie() {
    string ret = lower_case(specie);
    if (ret[0] == 'a') {
        return "an " + ret; 
    }
    else {
        return ret;
    }
}