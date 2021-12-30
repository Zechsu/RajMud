private mapping skills = ([]);
private mapping exp = ([]);

int query_skill_level(string skill) {
    return skills[skill];
}

int query_skill_exp(string skill) {
    return exp[skill];
}

mapping query_skills() {
    return copy(skills);
}

void set_skill_level(string skill, int level) {
    skills[skill] = level;
}

void add_skill(string skill) {
    skills[skill] = 1;
}

void give_exp(string skill, int amt) {
    int required_exp;
    if (!skills[skill]) {
        add_skill(skill);
    }
    exp[skill] += amt;
    // TODO: Levelling
}