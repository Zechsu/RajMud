#include <globals.h>

#define KABUTO_COLORS       ({"%#b2633e%#", "%#6a2f18%#", "%#98723b%#"})
#define SPECIES             ({"Allomyrina dichotoma dichotoma", "Allomyrina dichotoma inchachina", "Allomyrina dichotoma septentrionalis"})

inherit LIB_ITEM;

int health;
int max_health;
int attack;
string owner;

int idx = secure_random(sizeof(SPECIES));
string col;
string specie;
int has_horn;

void set_stats();
int set_horn(int horn);
int set_owner(string ow);
void setup();

void create() {
    ::create();
    setup();
    set_short(col + "kabuto%^RESET%^");
    set_long("A lovely " + col + "kabuto!%^RESET%^");
    set_ids(({"kabuto"}));
    set_stats();
    set_horn(1);
}

void setup() {
    col = KABUTO_COLORS[idx];
    specie = SPECIES[idx];
}

string query_long() {
    string ret = item::query_long();
    return has_horn? ret : ret + " Its horn is missing!";
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

void set_stats() {
    if (specie == SPECIES[0]) {
        attack = 4;
        health = 35;
        max_health = 35;
        return;
    }
    if (specie == SPECIES[1]) {
        attack = 5;
        health = 30;
        max_health = 30;
        return;
    }
    if (specie == SPECIES[2]) {
        attack = 3;
        health = 39;
        max_health = 39;
        return;
    }
    return;
}

int set_horn(int horn) {
    has_horn = horn;
    return 1;
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

int query_horn() {
    return has_horn;
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

int get_damage() {
    if (has_horn) {
        return secure_random(attack+1);
    }
    else {
        return secure_random(attack);
    }
}

string query_owner() {
    return owner;
}

int set_owner(string ow) {
    owner = ow;
    return 1;
}

int take_damage(int dmg) {
    health -= dmg;
    if (health <= 0) {
        health = 0;
        return 0;
    }
    return 1;
}

int is_dead() {
    return health <= 0;
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

int set_specie(mixed spec) {
    if (stringp(spec)) {
        idx = member_array(spec, SPECIES);
    }
    else if (intp(spec) && spec >= 0) {
        if (spec < sizeof(SPECIES)) {
            idx = spec;
        }
        else {
            return 0;
        }
    }
    create();
    return 1;
}

int heal() {
    health = max_health;
    return 1;
}

int lose_horn() {
    if (has_horn == 1) {
        has_horn = 0;
        return 1;
    }
    return 0;
}