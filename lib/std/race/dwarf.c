#include <globals.h>

inherit LIB_BODY;

void create() {
    ::create();
}

string query_race_name() {
    return "dwarf";
}

mapping query_race_body() {
    return (["head":(["critical":1, "parent":0])]);
}
