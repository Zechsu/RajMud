#include <globals.h>

inherit LIB_ITEM;
inherit M_SKILLS;

int has_horn;
string owner;

void heal();

void create() {
    ::create();
    set_short("beetle");
    set_long("A lovely beetle!");
    set_ids(({"beetle"}));
    set_skill_level("attack", 1);
    set_skill_level("max_health", 5);
    heal();
}

int has_horn() {
    return has_horn;
}

int is_fighter_beetle() {
    return 1;
}

string query_owner() {
    return owner;
}

int set_owner(string ow) {
    owner = ow;
    return 1;
}

string query_long() {
    string ret = item::query_long();
    if (has_horn) {
        ret += " It's horn is missing!";
    }
    return ret;
}

int can_get(object who) {
    object env = ENV(this_object());
    if (env->is_kabuto_arena()) {
        if (env->is_full()) {
            return 0;
        }
    }
    return 1;
}

int get_damage() {
    if (has_horn) {
        return secure_random(query_skill_level("attack")+2);
    }
    else {
        return secure_random(query_skill_level("attack")+1);
    }
}

int is_dead() {
    return query_skill_level("health") <= 0;
}

int take_damage(int dmg) {
    set_skill_level("health", query_skill_level("health") - dmg);
    if (query_skill_level("health") <= 0) {
        set_skill_level("health", 0);
        return 0;
    }
    return 1;
}

int do_attack(object target, int dmg) {
    if (target->is_kabuto()) {
        target->take_damage(dmg);
        return 1;
    }
    else {
        return 0;
    }
}

int lose_horn() {
    if (has_horn == 1) {
        has_horn = 0;
        return 1;
    }
    return 0;
}

void heal() {
    set_skill_level("health", query_skill_level("max_health"));
}