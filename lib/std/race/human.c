#include <globals.h>

inherit LIB_RACE;

void create() {
    ::create();
}

string query_race_name() {
    return "human";
}

mapping query_race_body() {
    return (["head":(["critical":1, "parent":0])]);
}
