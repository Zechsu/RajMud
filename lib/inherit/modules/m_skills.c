#include <globals.h>

private mapping skills = ([]);

void create() {}

int query_skill_level(string skill) {
    if (skills[skill]) {
        return skills[skill];
    }
    else {
        return 0;
    }
}

mapping query_skills() {
    return skills;
}

int set_skill_level(string skill, int level) {
    skills[skill] = level;
    return 1;
}
