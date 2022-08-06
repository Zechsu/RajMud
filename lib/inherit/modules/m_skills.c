#include <daemons.h>

private mapping skills = ([]);

int query_skill_level(string skill) {
    if (skills[skill])
        return skills[skill]["level"];
    else
        return 0;
}

int query_skill_exp(string skill) {
    if (skills[skill])
        return skills[skill]["exp"];
    else
        return 0;
}

string* query_skills() {
    return keys(skills);
}

void set_skill_level(string skill, int level) {
    if (skills[skill])
        skills[skill]["level"] = level;
    else
        skills += ([skill:(["level":level, "exp":0])]);
}

void remove_skill(string skill) {
    map_delete(skills, skill);
}

void add_skill(string skill) {
    skills += ([skill:(["level":1, "exp":0])]);
}

void give_exp(string skill, int amt) {
    int required_exp, skill_max_level;
    //int required_exp;
    if (!skills[skill]) {
        add_skill(skill);
    }

    required_exp = Skill(skill)->required_exp(skills[skill]["level"]);
    skill_max_level = Skill(skill)->query_max_level();

    skills[skill]["exp"] += amt;
    // If enough exp to level up and below max level
    if (skills[skill]["exp"] >= required_exp && skills[skill]["level"] < skill_max_level) {
        skills[skill]["exp"] -= required_exp;
        skills[skill]["level"] += 1;
    }
}