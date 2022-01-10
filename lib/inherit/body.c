/**
 * @file body.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief The body object of every living object
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <globals.h>
#include <modules.h>
#include "include/race.h"
#include "include/body.h"

inherit M_GENDER;

private mapping limbs = ([]);

void create() {
     if (!limbs) {
          limbs = ([]);
     }
}

/**
 * @brief Returns keys of limbs mapping
 * 
 * @return string* Keys of limbs
 */
string* query_limbs() {
     return (limbs? keys(limbs) : 0);
}

/**
 * @brief Returns a random limbo from the mapping
 * 
 * @return string Random limb
 */
string query_random_limb() {
     return element_of(query_limbs());
}

/**
 * @brief Damages a limb
 * 
 * @param damage Amount of damage
 * @param limb Which limb
 * @return int
 */
varargs int event_receive_damage(int damage, string limb) {
     // If no limb is passed, get a random one
     if (!limb) {
          limb = query_random_limb();
     }
     limbs[limb]["health"] -= damage;
}

/**
 * @brief Returns limbs full mapping
 * 
 * @return mapping Limbs
 */
mapping query_body() {
     return limbs;
}

/**
 * @brief Create a new body \n
 * This will completely override the object's limbs based on the race give.
 * @param race Race name
 * @return int 
 */
int create_new_body(string race) {
     if (!race) {
          debug_message("No race given for body creation\n");
          return 0;
     }
     if (!RACE_D->is_valid_race(race)) {
          debug_message("Invalid race as argument for create_new_body() - Race given: " + race + "\n");
          return 0;
     }
     limbs = Race(race)->query_race_body();
     return 1;
}
