#include <globals.h>
#include "include/race.h"

inherit BASE;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;

private mapping limbs = ([]);
private string current_room;

void create_new_body(string);

void create() {
     m_description::create();
     m_skills::create();
     if (!current_room) {
          current_room = TEST_ROOM;
     }
     if (!limbs) {
          limbs = ([]);
     }
}

mapping query_limbs() {
     return limbs;
}

int create_new_body(string race) {
     if (!race) {
          debug_message("No race given for body creation\n");
          return 0;
     }
     if (!RACE_D->is_valid_race(race)) {
          debug_message("Invalid race as argument for create_new_body() - Race given: " + race + "\n");
          return 0;
     }
     limbs = RACE_D->query_race_filename(race)->query_race_body();
     return 1;
}

varargs int move(mixed dest, int flag) {
     ::move(dest);
     if (!flag) {
          current_room = dest;
     }
}

string query_current_room() {
     return current_room;
}
