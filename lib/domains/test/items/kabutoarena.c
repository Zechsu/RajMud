#include <globals.h>

inherit LIB_ITEM;

object kab1, kab2;

void create() {
    ::create();
    set_short("kabuto arena");
    set_long("An empty kabuto arena");
    set_ids(({"kabuto arena", "arena"}));
}

void init() {
    add_action("do_get", "get");
}

int do_get(string str) {
    if (!str) {
        return 0;
    }
    str = replace_string(str, "the", "");
    if (str == "kabuto arena" || str == "kabuto from arena") {
        if (kab1 && kab2) {
            write("You can't do that during a fight!\n");
            return 1;
        }
        else {
            if (kab1) {
                if (kab1->event_get(this_player())) {
                    write("You get the " + kab1->query_short() + ".\n");
                    kab1 = 0;
                }
                return 1;
            }
            else if (kab2 != 0) {
                if (kab2->event_get(this_player())) {
                    write("You get the " + kab2->query_short() + ".\n");
                    kab2 = 0;
                }
                return 1;
            }
        }
    }
    return 0;
}

string query_long() {
    if (kab1 && !kab2) {
        return "A " + kab1->query_short() + " awaits its opponent.";
    }
    else if (kab1 && kab2) {
        return "A fierce fight is taking place on the arena!";
    }
    else {
        return item::query_long();
    }
}

int put_kabuto(object kab) {
    object tp = this_player();
    if (!kab1 || !kab2) {
        if (kab->is_kabuto()) {
            if (!kab1) {
                kab1 = kab;
                kab->move(this_object());
                tp->remove_item_from_inventory(kab);
                return 1;
            }
            if (!kab2) {
                kab2 = kab;
                kab->move(this_object());
                tp->remove_item_from_inventory(kab);
                set_heart_beat(3);
                return 1;
            }
        }
    }
    else {
        return 0;
    }
}

int can_get() {
    return 0;
}

void heart_beat() {
    if (kab1 && kab2) {
        int dmg1 = kab1->get_damage();
        int dmg2 = kab2->get_damage();
        if (dmg1 == 0) {
            say("The " + kab1->query_short() + " [" + kab1->query_owner() +"] goes for an attack, but it misses!\n");
        }
        else {
            say("The " + kab1->query_short() + " [" + kab1->query_owner() + "] strikes!\n");
            if (kab2->take_damage(dmg1) == 0) {
                say("The " + kab2->query_short() + " [" + kab1->query_owner() + "] falls down!\n");
                destruct(kab2);
                kab2 = 0;
                set_heart_beat(0);
                return;
            }
        }
        if (dmg2 == 0) {
            say("The " + kab2->query_short() + " [" + kab2->query_owner() + "] goes for an attack, but it misses!\n");
        }
        else {
            say("The " + kab2->query_short() + " [" + kab2->query_owner() + "] strikes back!\n");
            if (kab1->take_damage(dmg1) == 0) {
                say("The " + kab1->query_short() + " [" + kab2->query_owner() +"] falls down!\n");
                destruct(kab1);
                kab1 = 0;
                set_heart_beat(0);
                return;
            }
        }
    }
}