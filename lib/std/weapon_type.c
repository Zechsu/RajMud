private string name;
private mapping attacks;
private mapping weapon_skills;

void set_name(string n) {
    name = n;
}

void set_attacks(mapping att) {
    attacks = att;
}

void set_weapon_type_skills(mapping skills) {
    weapon_skills = skills;
}

string query_name() {
    return name;
}

mapping query_attacks() {
    return copy(attacks);
}