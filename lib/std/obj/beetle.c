#include <lib.h>
#include <modules.h>
#include "include/beetle.h"

inherit LIB_ITEM;
inherit M_SKILLS;

int has_horn;
string owner;
object target;
int special_attack_chance;
function special_attack;

void create() {
    ::create();
    set_short("beetle");
    set_long("A lovely " + query_short() + "!");
    set_ids(({"beetle"}));
    set_skill_level("attack", 1);
    set_skill_level("max_health", 5);
    set_special_attack_chance(0);
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

void set_target(object t) {
    target = t;
}

object query_target() {
    return target;
}

string query_long() {
    string ret = item::query_long();
    if (has_horn) {
        ret += " It's horn is missing!";
    }
    return ret;
}

// if flag is set, it will return only the name without "beetle" at the end
// this is for getting a "species" name for example corpse of query_short(1) => corpse of stag
varargs string query_short(int flag) {
    string ret = ::query_short();
    if (flag) {
        return ret;
    }
    return ret + " beetle";
}

int can_get(object who) {
    object env = ENV(this_object());
    if (env->is_beetle_arena()) {
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

int lose_horn() {
    if (has_horn == 1) {
        has_horn = 0;
        return 1;
    }
    return 0;
}

void set_special_attack(function f) {
    special_attack = f;
}

mixed event_special_attack() {
    if (special_attack_chance && special_attack) {
        int roll = secure_random(101);
        if (roll > 100-special_attack_chance) {
            return (*special_attack)();
        }
    }
    return 0;
}

void set_special_attack_chance(int chance) {
    if (chance > 100) {
        special_attack_chance = 100;
    }
    else if (chance < 0) {
        special_attack_chance = 0;
    }
    else {
        special_attack_chance = chance;
    }
}

varargs void heal(int amt) {
    int maxhp = query_skill_level("max_health");
    if (!amt) {
        set_skill_level("health", maxhp);
    }
    if (amt > maxhp) {
        set_skill_level("health", maxhp);
    }
    else {
        set_skill_level("health", query_skill_level("health")+amt);
    }
    
}
