#include <globals.h>
#include <limb.h>
#include <attributes.h>
#include <flags/limbs_flags.h>

private string race;
private string* race_groups, *race_traits;
private mapping body, attacks;

void set_race_name(string n) {
    race = n;
}

string query_race_name() {
    return copy(race);
}

mapping query_race_body() {
    return copy(body);
}

string* query_race_traits() {
    return race_traits;
}

void set_race_traits(string* traits) {
    race_traits = traits;
}

string* query_race_groups() {
    return race_groups;
}

void set_race_groups(string* groups) {
    race_groups = groups;
}

void set_race_attacks(mapping new_attacks) {
    attacks = new_attacks;
}

mapping query_race_attacks() {
    return copy(attacks);
}

void set_race_body(mapping b) {
    body = b;
}

int query_fingers(string hand) {
    if (body[hand]["fingers"]) {
        return body[hand]["fingers"];
    }
    return 0;
}

int is_severable(string limb) {
    return !(body[limb]["flags"] & LIMB_NOT_SEVERABLE);
}

void set_limb(class Limb_t limb) {
    body[limb->name] = ([
        "flags": limb->flags,
        "parent": limb->parent,
        "worn": ({}),
        "type": limb->type,
        "factor": limb->factor,
        "max_hp": 0,
        "current_hp": 0,
    ]);
}

float calculate_damage_rating(object who) {
    return 0.15 * diminishing_returns(who->query_attribute(NORMAL_STRENGTH), 70);
}

float event_strike(object target) {
    return calculate_damage_rating(this_player());
}
