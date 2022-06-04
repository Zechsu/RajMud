#include <flags/limbs_flags.h>

inherit STD_RACE;

void create() {
    set_race_name("human");
    set_race_body(([
        "head":([
            "flags": LIMB_CRITICAL,
            "parent":0,
            "worn": ({}),
            "type":"head",
            "factor":0.35,
            "max_hp":0,
            "current_hp":0,
        ]),
        "torso":([
            "flags": LIMB_CRITICAL | LIMB_NOT_SEVERABLE,
            "parent":0,
            "worn": ({}),
            "type":"torso",
            "factor":0.5,
            "max_hp":0,
            "current_hp":0,
        ]),
        "right arm":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"arm",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "left arm":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"arm",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "right leg":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"leg",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "left leg":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"leg",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "right hand":([
            "flags": 0,
            "parent":"right arm",
            "fingers":5,
            "worn": ({}),
            "type":"hand",
            "factor":0.15,
            "max_hp":0,
            "current_hp":0,
        ]),
        "left hand":([
            "flags": 0,
            "parent":"left arm",
            "fingers":5,
            "worn": ({}),
            "type":"hand",
            "factor":0.15,
            "max_hp":0,
            "current_hp":0,
        ]),
        "genitals":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"genitals",
            "factor":0.05,
            "max_hp":0,
            "current_hp":0,
        ]),
    ]));
}

// List of limbs that act as legs
// Used to check if living is able to stand
string* query_legs() {
    return ({"right leg", "left leg"});
}

// List of limbs that act as arms
string* query_hands() {
    return ({"right hand", "left hand"});
}

// Name of a limb that will be matched and used to determine if a entity has at least 1 usable hand
// For example used to check if has a hand to get things
string query_hand() {
    return "hand";
}

string query_attack_message() {
    return element_of(({"$N $vpunch $T",
                        "$N $vkick $T"}));
}

// Will calculate the max health of a limb 
// Used when leveling up, so limbs have correct stats
int calculate_health_of_limb(string limb) {
    int const = this_player()->query_skill_level("constitution");
    return 28 * const * query_race_body()[limb]["factor"];
}