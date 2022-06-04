#include <flags/limbs_flags.h>

inherit STD_RACE;

void create() {
    set_race_name("rodent");
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
        "right paw":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"arm",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "left paw":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"arm",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "right hind leg":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"leg",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "left hind leg":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"leg",
            "factor":0.25,
            "max_hp":0,
            "current_hp":0,
        ]),
        "tail":([
            "flags": 0,
            "parent":"torso",
            "worn": ({}),
            "type":"tail",
            "factor":0.05,
            "max_hp":0,
            "current_hp":0,
        ]),
    ]));
}

// List of limbs that act as legs
// Used to check if living is able to stand
string* query_legs() {
    return ({"right hind leg", "left hind leg"});
}

// List of limbs that act as arms
string* query_hands() {
    return ({"right paw", "left paw"});
}

// Name of a limb that will be matched and used to determine if a entity has at least 1 usable hand
// For example used to check if has a hand to get things
string query_hand() {
    return "paw";
}

string query_attack_message() {
    return element_of(({"$N $vscratch $T",
                        "$N $vbite $T"}));
}

// Will calculate the max health of a limb 
// Used when leveling up, so limbs have correct stats
int calculate_health_of_limb(string limb) {
    int const = this_player()->query_skill_level("constitution");
    return 14 * const * query_race_body()[limb]["factor"];
}