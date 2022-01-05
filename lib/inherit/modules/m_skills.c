private mapping skills = ([]);

int query_skill_level(string skill) {
    return skills[skill]["level"];
}

int query_skill_exp(string skill) {
    return skills[skill]["exp"];
}

string* query_skills() {
    return keys(skills);
}

void set_skill_level(string skill, int level) {
    skills[skill]["level"] = level;
}

void add_skill(string skill) {
    skills[skill] = (["level":1]);
}

void give_exp(string skill, int amt) {
    //int required_exp;
    if (!skills[skill]) {
        add_skill(skill);
    }
    skills[skill]["exp"] += amt;
    // TODO: Levelling
}