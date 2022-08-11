#include <flags/limbs_flags.h>

inherit STD_RACE;

void create() {
    set_race_name("dummy");
    set_race_body(([
        "head":([
            "flags": 0,
            "parent":0,
            "worn": ({}),
            "type":"head",
            "factor":0.35,
            "max_hp":0,
            "current_hp":0,
        ]),
        "torso":([
            "flags": 0,
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

// Will calculate the max health of a limb 
// Used when leveling up, so limbs have correct stats
int calculate_health_of_limb(string limb) {
    int const = this_player()->query_skill_level("constitution");
    return 28 * const * query_race_body()[limb]["factor"];
}