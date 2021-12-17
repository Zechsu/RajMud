#include <globals.h>
#include "include/race.h"
#include "include/body.h"

private mapping limbs = ([]);

void create() {
     if (!limbs) {
          limbs = ([]);
     }
}

string* query_limbs() {
     return (limbs? keys(limbs) : 0);
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
     limbs = RACE_D->query_race_file(race)->query_race_body();
     return 1;
}
