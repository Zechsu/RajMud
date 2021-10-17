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
                say(tp->query_name() + " puts his " + kab1->query_short() + " in the arena.\n");
                return 1;
            }
            if (!kab2) {
                kab2 = kab;
                kab->move(this_object());
                tp->remove_item_from_inventory(kab);
                say(tp->query_name() + " puts his " + kab2->query_short() + " in the arena.\n");
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

string get_attack_mess(object kab, object target) {
    string kab_name = sprintf("%s [%s]", kab->query_short(), kab->query_owner());
    string target_name = sprintf("%s [%s]", target->query_short(), target->query_owner());
    string ret = "";
    switch(secure_random(2)) {
        case 0: {
            ret = sprintf("%s strikes!\n", kab_name);
            break;
        }
        case 1: {
            ret = sprintf("%s bashes %s\n", kab_name, target_name);
            break;
        }
        default: {
            ret = sprintf("%s strikes!\n", kab_name);
            break;
        }
    }

    return ret;
}

void do_fight(object kab, object target) {
    int dmg = kab->get_damage();
    if (dmg == 0) {
        say(kab->query_short() + " [" + kab->query_owner() +"] goes for an attack, but it misses!\n");
    }
    else {
        say(get_attack_mess(kab, target));
        if (secure_random(21) == 0) {
            target->lose_horn();
            say(sprintf("%s [%s] loses its horn!\n", target->query_short(), target->query_owner()));
        }
        if (target->take_damage(dmg) == 0) {
            say(target->query_short() + " [" + target->query_owner() + "] falls down!\n");
            destruct(target);
        }
    }
}

void heart_beat() {
    if (kab1 && kab2) {
        do_fight(kab1, kab2);
        do_fight(kab2, kab1);
    }
    else {
        set_heart_beat(0);
    }
}
