#include <globals.h>

inherit LIB_CONTAINER;

object beetle1, beetle2;

void create() {
    ::create();
    set_short("kabuto arena");
    set_long("An empty kabuto arena");
    set_ids(({"kabuto arena", "arena"}));
    set_capacity(2);
}

void update_kabs() {
    object* inv = all_inventory(this_object());
    if (sizeof(inv) == 1) {
        beetle1 = inv[0];
    }
    if (sizeof(inv) == 2) {
        beetle1 = inv[0];
        beetle2 = inv[1];
    }
}

int is_kabuto_arena() {
    return 1;
}

string query_long() {
    object* inv = all_inventory(this_object());
    if (sizeof(inv) == 1) {
        return "A " + inv[0]->query_short() + " awaits its opponent.";
    }
    else if (sizeof(inv) == 2) {
        return "A fierce fight is taking place on the arena!";
    }
    else {
        return ::query_long();
    }
}

string query_contents_mess() {
    return query_long();
}

mixed event_recieve_item(object item, object who) {
    mixed b;
    if (!who) {
        who = this_player();
    }
    if (!item->is_fighter_beetle()) {
        return "That is not a fighter beetle!\n";
    }
    b = ::event_recieve_item(item, who);
    if (b == 1) {
        say(sprintf("%s puts %s in the arena!\n", who->query_name(), item->query_short()));
        item->set_owner(who->query_name());
        update_kabs();
        if (beetle1 && beetle2) {
            beetle1->set_target(beetle2);
            beetle2->set_target(beetle1);
            set_heart_beat(3);
        }
    }
    return b;
}

int can_get(object who) {
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
    mixed result = kab->event_special_attack();
    if (stringp(result)) {
        say(result);
    }
    else {
        int dmg = kab->get_damage();
        if (dmg == 0) {
            say(kab->query_short() + " [" + kab->query_owner() +"] goes for an attack, but it misses!\n");
        }
        
        else {
            say(get_attack_mess(kab, target));
            if (secure_random(41) == 0) {
                target->lose_horn();
                say(sprintf("%s [%s] loses its horn!\n", target->query_short(), target->query_owner()));
            }
            target->take_damage(dmg);
        }
    }
    if (target->is_dead()) {
            say(target->query_short() + " [" + target->query_owner() + "] falls down!\n");
            destruct(target);
    }
}

void heart_beat() {
    if (beetle1 && beetle2) {
        do_fight(beetle1, beetle2);
        do_fight(beetle2, beetle1);
    }
    else {
        set_heart_beat(0);
    }
}
