private mapping traits = ([]);

mapping query_traits() {
    return traits;
}

int query_trait(string trait) {
    if (traits[trait]) {
        return traits[trait];
    }
    return 0;
}

int set_trait(string trait, mixed value) {
    traits[trait] = value;
    return 1;
}

void add_trait(string trait, mixed amount) {
    traits[trait] += amount;
}

void subtract_trait(string trait, mixed amount) {
    traits[trait] -= amount;
}