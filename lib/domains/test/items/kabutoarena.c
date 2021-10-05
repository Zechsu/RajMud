#include <globals.h>

inherit LIB_ITEM;

object kab1, kab2;

void create() {
    ::create();
    set_short("kabuto arena");
    set_long("An empty kabuto arena");
    set_ids(({"kabuto arena", "arena"}));
    set_heart_beat(3);
}

string query_long() {
    if (kab1) {
        return "A " + kab1->query_short() + " awaits its opponent.";
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
        say("KABUTO FIGHT WOO\n");
    }
}