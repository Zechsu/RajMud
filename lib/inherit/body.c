#include <globals.h>

private mapping traits = ([]);

void create() {
    if (!sizeof(traits)) {
        traits = ([]);
    }
}

mapping query_traits() {
    return traits;
}

int query_trait(string trait) {
    if (traits[trait]) {
        return traits[trait];
    }
    else {
        return 0;
    }
}

int set_trait(string trait, mixed value) {
    traits[trait] = value;
    return 1;
}