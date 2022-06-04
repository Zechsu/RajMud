#include <globals.h>
#include <limb.h>
#include <flags/limbs_flags.h>

private string race;
private mapping body;

void set_race_name(string n) {
    race = n;
}

string query_race_name() {
    return copy(race);
}

mapping query_race_body() {
    return copy(body);
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