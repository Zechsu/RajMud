#include <attributes.h>

string query_name() {
    return "club";
}

string* query_attacks() {
    return ({"bash"});
}

float calculate_damage_rating(object who) {
    return  diminishing_returns(who->query_skill_level("blunt"), 300) + 
            0.75 * diminishing_returns(who->query_attribute(NORMAL_STRENGTH), 80);
}