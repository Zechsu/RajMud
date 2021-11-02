#include <globals.h>

inherit USER_OB;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;

private mapping limbs = ([]);

string query_name();
mapping query_race_body();

void create() {
    user::create();
    m_description::create();
    m_skills::create();
}

string query_long() {
    return sprintf("%s is nondescript.", query_name());
}

mapping query_limbs() {
    return limbs;
}

void new_body(string race) {
    if (!race) {
        debug_message("No race given for body creation\n");
        return;
    }
    limbs = RACE_D->query_race_filename(race)->query_race_body();
}
