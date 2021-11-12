#include <globals.h>

inherit LIB_BODY;

private string race;

void create() {
    ::create();
}

string query_race_name() {
    return "Undefined race name\n";
}

mapping query_race_body() {
    // this should return a limbs mapping for when we create a new body
    // returns an empty mapping in case we forget to set one up lol
    return ([]);
}

int set_race(string r) {
    if (!RACE_D->is_valid_race(r)) {
        debug_message("Invalid race as arg for set_race() - Race given: " + r + "\n");
        return 0;
    }
    race = RACE_D->query_race_filename(r)->query_race_name();
    create_new_body(race);
    return 1;
}

string query_race() {
    return race;
}
