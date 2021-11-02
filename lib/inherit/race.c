#include <globals.h>

inherit LIB_BODY;

void create() {
    body::create();
}

string query_race_name() {
  return "Undefined race name\n";
}

mapping query_race_body() {
    // this should return a limbs mapping for when we create a new body
    // returns an empty mapping in case we forget to set one up lol
    return ([]);
}
