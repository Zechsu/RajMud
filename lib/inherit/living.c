#include <globals.h>

inherit LIB_RACE;

string query_name();

void create() {
    ::create();
}

string query_long() {
     return sprintf("%s is nondescript.", query_name());
}
