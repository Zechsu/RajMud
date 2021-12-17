#include <globals.h>

inherit LIB_BODY;

private string race;

void create() {
    body::create();
    if (!race) {
        race = "Undefined race";
    }
}

string query_race() {
  return race;
}

int set_race(string r) {
    if (!RACE_D->is_valid_race(r)) {
        debug_message("Invalid race as arg for set_race() - Race given: " + r + "\n");
        return 0;
    }
    race = RACE_D->query_race_file(r)->query_race_name();
    create_new_body(race);
    return 1;
}
