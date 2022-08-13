#include <attributes.h>

string query_name() {
    return "slingshot";
}

string* query_attacks() {
    return ({"shoot"});
}

float calculate_damage_rating(object who) {
    return  diminishing_returns(who->query_skill_level("ranged"), 100) + 
            0.5 * diminishing_returns(who->query_attribute(NORMAL_STRENGTH), 70);
}