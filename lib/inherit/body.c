#include <globals.h>

inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;

string query_name();

void create() {
}

string query_long() {
    return sprintf("%s is nondescript.", query_name());
}
