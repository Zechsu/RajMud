#include <daemons.h>
#include <armor_layers.h>
#include "../include/race.h"

private nosave mapping attacks;
private nosave int attacks_dirty = 1;

varargs void setup_race_attacks(int forced) {
    if (attacks_dirty || forced) {
        mapping race_attacks = Race(this_object()->query_race())->query_race_attacks();
        string* keys;

        if (!race_attacks)
            return;
        
        keys = keys(race_attacks);

        if (!attacks) {
            attacks = ([]);
        }

        foreach (string key in keys) {
            attacks[key] = ([
                "name"     : key,
                "priority" : race_attacks[key],
                "enabled"  : 1,
                "source"   : Race(this_object()->query_race())
            ]);
        }
    }
}

varargs void setup_weapon_attacks(int forced) {
    if (attacks_dirty || forced) {
        object* weapons = this_object()->query_worn(0, A_WEAPON);
        int* weapon_types = weapons->query_weapon_type();
        mapping weapon_attacks = ([]);
        string* keys;
        int dups = 0;

        if (!attacks) {
            attacks = ([]);
        }

        for (int i = 0; i < sizeof(weapon_types); i++) {
            weapon_attacks = WEAPON_TYPES_D->query_weapon_type(weapon_types[i])->query_attacks();
            keys = keys(weapon_attacks);
            if (!keys)
                continue;

            foreach (string attack in keys) {
                string tmp = attack;
                // Can't use same name for attack just add indexing
                if (attacks[tmp]) {
                    tmp = attack + "-" + dups;
                    dups = dups + 1;
                }
                attacks[tmp] = ([
                    "name"     : attack,
                    "priority" : weapon_attacks[attack],
                    "enabled"  : 1,
                    "source"   : weapons[i]
                ]);
            }
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

varargs mapping query_attacks(function filter) {
    if (attacks_dirty) {
        setup_race_attacks(1);
        setup_weapon_attacks(1);
        attacks_dirty = 0;
    }
    
    if (filter)
        return filter_mapping(copy(attacks), filter);
    return copy(attacks);
}

varargs mapping query_enabled_attacks(function filter) {
    mapping ret = query_attacks(filter);
    string* ats = keys(ret);
    foreach (string key in ats) {
        if (ret[key]["enabled"] == 0) {
            map_delete(ret, key);
        }
    }

    return ret;
}

mapping query_attacks_priority(function filter) {
    mixed tmp = query_enabled_attacks(filter);
    mapping ret = ([]);
    string* ats = keys(tmp);
    foreach (string key in ats) {
        ret[key] = tmp[key]["priority"];
    }

    return ret;
}

// Returns a random attack
varargs string query_random_attack(int flag) {
    mapping weights = ([]);
    mapping en_attacks = query_enabled_attacks();
    string* ats = keys(en_attacks);
    string attack;
    foreach (string key in ats) {
        weights[key] = en_attacks[key]["priority"];
    }

    attack = element_of_weighted(weights);
    return copy(attacks[attack]);
}