#include <daemons.h>
#include <armor_layers.h>
#include "../include/race.h"

private nosave mapping attacks;
private nosave int attacks_dirty = 1;

varargs void setup_race_attacks(int forced) {
    if (attacks_dirty || forced) {
        mapping race_attacks = Race(this_object()->query_race())->query_race_attacks();
        string* keys = keys(race_attacks);
        if (!attacks) {
            attacks = allocate_mapping(sizeof(keys));
        }
        foreach (string key in keys) {
            attacks[key] = ([
                "priority" : race_attacks[key],
                "enabled"  : 1
            ]);
        }
    }
}

varargs void setup_weapon_attacks(int forced) {
    if (attacks_dirty || forced) {
        string* weapon_attacks = this_object()->query_worn(0, A_WEAPON)->query_attacks();
        weapon_attacks = decompose(weapon_attacks);
        if (!attacks) {
            attacks = allocate_mapping(sizeof(weapon_attacks));
        }
        foreach (string attack in weapon_attacks) {
            attacks[attack] = ([
                "priority" : 12,
                "enabled"  : 1
            ]);
        }
    }
}

void set_attacks_dirty() {
    attacks_dirty = 1;
}

int disable_attack(string attack) {
    if (attacks[attack]) {
        attacks[attack]["enabled"] = 0;
        return 1;
    }
    return 0;
}

int enable_attack(string attack) {
    if (attacks[attack]) {
        attacks[attack]["enabled"] = 1;
        return 1;
    }
    return 0;
}

int is_attack_enabled(string attack) {
    if (attacks[attack])
        return attacks[attack]["enabled"];
    return 0;
}

mapping query_attacks(function filter) {
    if (attacks_dirty) {
        setup_race_attacks(1);
        setup_weapon_attacks(1);
        attacks_dirty = 0;
    }
    
    if (filter)
        return filter_mapping(copy(attacks), filter);
    return copy(attacks);
}