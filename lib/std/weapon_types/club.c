#include <attributes.h>
#include <priorities.h>
#include <lib.h>

inherit LIB_WEAPON_TYPE;

void create() {
    set_name("club");
    set_attacks(([
        "bash": Priority_High
    ]));
}

float calculate_damage_rating(object who) {
    return  diminishing_returns(who->query_skill_level("blunt"), 300) + 
            0.17 * diminishing_returns(who->query_attribute(NORMAL_STRENGTH), 80);
}