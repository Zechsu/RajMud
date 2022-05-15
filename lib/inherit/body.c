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
string query_name();
int event_die();
string query_pronoun();
string query_possessive_determiner();

private mapping limbs = ([]);
private nosave int is_dead = 0;

void create() {
     if (!limbs) {
          limbs = ([]);
     }
}

int is_dead() {
     return is_dead;
}

// Returns keys of limbs mapping
string* query_limbs() {
     return (limbs? keys(limbs) : 0);
}

// Returns a random limb from the mapping
// If flag is set it will return a limb that is not severed
varargs mixed query_random_limb(int flag) {
     if (flag) {
          string* tmp = query_limbs();
          tmp = filter_array(tmp, (:limbs[$1]["severed"] == 0:));
          tmp = filter_array(tmp, (: limbs[$1]["current_hp"] > -2.0 :));
          if (!sizeof(tmp)) {
               return 0;
          }
          return element_of(tmp);
     }
     return element_of(query_limbs());
}

// Damages a limb if it's not passed, picks a random limb
varargs int event_receive_damage(float damage, string limb) {
     // If no limb is passed, get a random one
     if (!limb) {
          limb = query_random_limb();
     }
     limbs[limb]["current_hp"] -= damage;
     if (limbs[limb]["current_hp"] <= -2) {
          sever_limb(limb);
     }

     if (is_dead) {
          event_die();
          return -1;
     }
}

// Returns full limbs mapping
mapping query_body() {
     return limbs;
}

// Create a new body
// This will completely overwrite the limbs mapping with that of the new one given by the race
int create_new_body(string race) {
     object raceob;
     if (!race) {
          debug_message("No race given for body creation\n");
          return 0;
     }
     if (!RACE_D->is_valid_race(race)) {
          debug_message("Invalid race as argument for create_new_body() - Race given: " + race + "\n");
          return 0;
     }
     raceob = Race(race);
     limbs = raceob->query_race_body();
     foreach (string limb in keys(limbs)) {
          limbs[limb]["max_hp"] = raceob->calculate_health_of_limb(limb);
          limbs[limb]["current_hp"] = limbs[limb]["max_hp"];
     }
     is_dead = 0;
     return 1;
}

void update_max_health() {
     object raceob = Race(query_race());
     foreach (string limb in keys(limbs)) {
          limbs[limb]["max_hp"] = raceob->calculate_health_of_limb(limb);
     }
}

void sever_limb(string limb) {
     object ob, *equip;
     if (!limbs) {
          return;
     }

     if (!limbs[limb] || limbs[limb]["severed"] != 0 || !Race(query_race())->is_severable(limb)) {
          return;
     }
     tell_object(this_object(), "Your " + limb + " is severed!\n");
     tell_object(this_object(), "Your " + limb + " falls on the ground.\n");
     tell_room(environment(this_object()), sprintf("%s's %s falls on the ground.\n", query_short(), limb), ({this_object()}));

     limbs[limb]["severed"] = 1;
     foreach (string other in keys(limbs)) {
          if (limbs[other]["parent"] == limb && limbs[other]["severed"] != 1) {
               limbs[other]["current_hp"] = -limbs[other]["max_hp"];
               sever_limb(other);
          }
     }

     // Severed limb object
     ob = new("/std/obj/limbs/" + limbs[limb]["type"], query_race());
     ob->move(environment(this_object()));

     // This needs to be after the severing, so the limb is moved to the room the living died
     if (limbs[limb]["critical"]) {
          is_dead = 1;
     }

     // Drop wielded/worn weapons
     equip = query_worn(limb);
     if (sizeof(equip)) {
          foreach (object eq in equip) {
               // Get all the limbs on which the item is worn
               string* worn = eq->query_worn();
               // Remove the cut-off limb from the item's worn variable
               eq->remove_worn(limb);
               // If no limb is left, then the item needs to go
               if (sizeof(find_limb(worn, 1)) == 0) {
                    eq->event_remove(1);
                    if (eq->is_wieldable()) {
                         // If it's a weapon then drop it
                         eq->event_drop(this_object());
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

int event_die() {
     object corpse = new(LIB_CORPSE);
     object to = this_object();

     corpse->set_short(sprintf("%s's corpse", query_name()));
     corpse->set_long(sprintf("The corpse of %s", query_name()));
     corpse->set_ids(({"corpse"}));
     corpse->set_adjectives(({query_name(), query_name() + "'s", query_race()}));
     corpse->move(environment(to));
     corpse->set_decay(10);
     to->move_inventory_to(corpse);
     tell_object(to, "\n\n%^RED%^%^BOLD%^YOU'VE DIED!%^RESET%^\n\n");
     to->move(TEST_ROOM);
     to->create_new_body(query_race());
}

string severed_attributes() {
     string ret = "%^RED%^" + capitalize(query_pronoun()) + " is missing " + query_possessive_determiner() + " ";
     string* keys = keys(limbs);
     string* severed = filter_array(keys, (: limbs[$1]["severed"] == 1 :));
     ret += list_strings(severed);
     if (sizeof(severed)) {
          return ret + "%^RESET%^";
     }
     return 0;
}