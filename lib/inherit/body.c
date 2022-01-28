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
#include <lib.h>
#include "include/race.h"
#include "include/body.h"

inherit M_GENDER;

string query_short();

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

void sever_limb(string limb) {
     object ob, equip;
     if (!limbs) {
          return;
     }
     if (!limbs[limb] || limbs[limb]["severed"] != 0) {
          return;
     }
     tell_object(this_object(), "Your " + limb + " is severed!\n");
     tell_object(this_object(), "Your " + limb + " falls on the ground.\n");
     tell_room(environment(this_object()), sprintf("%s's %s falls on the ground.\n", query_short(), limb), ({this_object()}));

     limbs[limb]["severed"] = 1;
     foreach (string other in keys(limbs)) {
          if (limbs[other]["parent"] == limb) {
               sever_limb(other);
          }
     }

     // Severed limb object
     ob = new("/std/obj/limb");
     ob->set_short(sprintf("severed %s %s", query_race(), limb));
     ob->set_long(sprintf("The remains of a %s %s", query_race(), limb));
     ob->set_ids(({"limb", limb}));
     ob->set_adjectives(({"severed", query_race()}));
     ob->move(environment(this_object()));
     ob->set_decay(5);

     // Drop wielded/worn weapons
     equip = query_worn(limb);
     if (equip) {
          foreach (object eq in equip) {
               // Get all the limbs on which the item is worn
               string* worn = eq->query_worn();
               // Remove the cut-off limb from the item's worn variable
               eq->remove_worn(limb);
               // If no limb is left, then the item needs to go
               if (!sizeof(find_limb(worn, 1))) {
                    eq->event_remove(1);
                    if (eq->is_wieldable()) {
                         // If it's a weapon then drop it
                         eq->event_drop();
                    }
                    else {
                         // Move to corpse
                         eq->move(ob);
                    }
               }
          }
     }

     this_object()->check_position();
}

varargs mixed query_worn(string limb, int layer) {
     if (!limb) {
          object* ret = ({});
          string* lkeys = keys(limbs);
          int sz = sizeof(limbs);
          for (int i = 0; i < sz; i++) {
               if (limbs[lkeys[i]]["worn"] == 0) {
                    continue;
               }
               else {
                    if (!layer) {
                         ret += limbs[lkeys[i]]["worn"];
                    }
                    else {
                         foreach (object worn in limbs[lkeys[i]]["worn"]) {
                              if (worn->query_layer() == layer) {
                                   ret += ({worn});
                              }
                         }
                    }
               }
          }
          return distinct_array(ret);
     }
     else {
          if (!layer) {
               return limbs[limb]["worn"];
          }
          else {
               object* ret = ({});
               foreach (object worn in limbs[limb]["worn"]) {
                    if (worn->query_layer() == layer) {
                         ret += ({worn});
                    }
               }
               return ret;
          }
     }
}

// If flag is on we'll find all limbs that are not severed
// Usually returns all limbs regardless if they're severed or not
varargs string* find_limb(string* match, int flag, int slot) {
     string* ret = ({});
     string* tmp;
     tmp = keys(limbs);
     if (flag) {
          tmp = filter_array(tmp, (: limbs[$1]["severed"] == 0 :));
     }
     if (slot) {
          foreach (string r in tmp) {
               foreach (object worn in query_worn(r)) {
                    if (worn->query_layer() == slot) {
                         tmp -= ({r});
                    }
               }
          }
     }
     foreach (string m in match) {
          foreach (string limb in tmp) {
               if (strsrch(limb, m) != -1) {
                    ret += ({limb});
               }
          }
     }
     return distinct_array(ret);
     // if (arrayp(match)) {
     //      foreach (string str in match) {
     //           foreach (string limb in keys(limbs)) {
     //                if (strsrch(limb, str) != -1) {
     //                     if (!flag)
     //                          ret += ({limb});
     //                     else {
     //                          if (limbs[limb]["severed"] == 0)
     //                               ret += ({limb});
     //                     }
     //                }
     //           }
     //      }
     // }
     // else {
     //      foreach (string limb in keys(limbs)) {
     //           if (strsrch(limb, match) != -1) {
     //                if (!flag)
     //                     ret += ({limb});
     //                else {
     //                if (limbs[limb]["severed"] == 0)
     //                     ret += ({limb});
     //                }
     //           }
     //      }
     // }
     // return ret;
}

int is_limb_severed(string limb) {
     return limbs[limb]["severed"];
}

int has_limbs(string* which) {
     string keys = implode(keys(limbs), ",");
     foreach (string w in which) {
          if (strsrch(keys, w) == -1) {
               return 0;
          }
     }
     return 1;
}