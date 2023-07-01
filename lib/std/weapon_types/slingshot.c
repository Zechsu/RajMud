#include <attributes.h>
#include <priorities.h>
#include <lib.h>

inherit LIB_WEAPON_TYPE;

void create() {
    set_name("slingshot");
    set_attacks(([
        "shoot": Priority_High
    ]));
}

float calculate_damage_rating(object who) {
    return  diminishing_returns(who->query_skill_level("ranged"), 100) + 
            0.10 * diminishing_returns(who->query_attribute(NORMAL_STRENGTH), 70);
}