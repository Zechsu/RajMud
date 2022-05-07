#include <lib.h>
#include <flags/item_flags.h>

inherit LIB_CONTAINER;

object beetle1, beetle2;

void create() {
    ::create();
    set_short("beetle arena");
    set_long("An empty beetle arena");
    set_ids(({"beetle arena", "arena"}));
    set_inventory_capacity(2);
    set_flag(ITEM_NO_GET);
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

int is_beetle_arena() {
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

varargs mixed event_recieve_item(object item, object who) {

    if (!who) {
        who = this_player();
    }
    if (!item->is_fighter_beetle()) {
        return notify_fail("That is not a fighter beetle!\n");
    }
    if (is_inventory_full()) {
        return notify_fail("The arena is full.\n");
    }
    item->move(TO);
    write(sprintf("You put %s in the arena.\n", item->query_short()));
    say(sprintf("%s puts %s in the arena!\n", who->query_name(), item->query_short()));
    item->set_owner(who->query_name());
    update_kabs();
    if (beetle1 && beetle2) {
        beetle1->set_target(beetle2);
        beetle2->set_target(beetle1);
        set_heart_beat(3);
    }
    return 1;
}

string get_attack_mess(object kab, object target) {
    string kab_name = capitalize(sprintf("%s [%s]", kab->query_short(), kab->query_owner()));
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
            say(capitalize(kab->query_short()) + " [" + kab->query_owner() +"] goes for an attack, but it misses!\n");
        }
        
        else {
            say(get_attack_mess(kab, target));
            if (secure_random(41) == 0) {
                target->lose_horn();
                say(sprintf("%s [%s] loses its horn!\n", capitalize(target->query_short()), target->query_owner()));
            }
            target->take_damage(dmg);
        }
    }
    if (target->is_dead()) {
            object corpse = new(LIB_CORPSE);
            corpse->set_short(sprintf("corpse of %s", target->query_short()));
            corpse->set_long("The remains of what used to be a living, breathing beetle. The smell reminds of rotten eggs and wet cat food.");
            corpse->set_ids(({"corpse", "beetle corpse", corpse->query_short(), target->query_short(1) + " corpse"}));
            corpse->set_decay(6);
            corpse->move(ENV(TO));
            say(sprintf("%s falls down on the ground.\n", capitalize(corpse->query_short())));
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
